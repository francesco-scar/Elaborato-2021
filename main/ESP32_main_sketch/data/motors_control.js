let motors_enabled = true;

document.getElementById('steps_slider').oninput = update_sliders;
document.getElementById('speed_slider').oninput = update_sliders;
document.getElementById('acceleration_slider').oninput = update_sliders;

function update_sliders () {
  document.getElementById('steps_label').innerText = document.getElementById('steps_slider').value;
  document.getElementById('speed_label').innerText = document.getElementById('speed_slider').value;
  if (document.getElementById('acceleration_slider').value == document.getElementById('acceleration_slider').max) {
    document.getElementById('acceleration_label').innerHTML = "&infin;";
  } else {
    document.getElementById('acceleration_label').innerText = document.getElementById('acceleration_slider').value;
  }
  
  update_plot();
}

function move_stepper (motion) {
  let acceleration_value = document.getElementById('acceleration_slider').value;
  if (acceleration_value == document.getElementById('acceleration_slider').max) {
    acceleration_value = 99999999999;       // I know it't terrible, but at least it works
  }
  ajax("/moveStepper?motion="+motion+"&steps="+document.getElementById('steps_slider').value+"&speed="+document.getElementById('speed_slider').value+"&acceleration="+acceleration_value, () => {});
}


function update_plot () {
  let canvas = document.getElementById('canvas_motor');
  let ctx = canvas.getContext("2d");
  ctx.clearRect(0, 0, canvas.width, canvas.height);
  
  // Origin (50, 300)
  drawLine(ctx, 50, 30, 50, 300, '#000');       // Y axis steps
  drawLine(ctx, 50, 300, 600, 300, '#000');     // X axis steps
  drawLine(ctx, 45, 40, 50, 30, '#000');        // Y axis arrow
  drawLine(ctx, 55, 40, 50, 30, '#000');
  drawLine(ctx, 590, 295, 600, 300, '#000');    // X axis arrow
  drawLine(ctx, 590, 305, 600, 300, '#000');
  
  // Origin (50, 600)
  drawLine(ctx, 50, 330, 50, 600, '#000');      // Y axis steps
  drawLine(ctx, 50, 600, 600, 600, '#000');     // X axis steps
  drawLine(ctx, 45, 340, 50, 330, '#000');      // Y axis arrow
  drawLine(ctx, 55, 340, 50, 330, '#000');
  drawLine(ctx, 590, 595, 600, 600, '#000');    // X axis arrow
  drawLine(ctx, 590, 605, 600, 600, '#000');

  let steps = document.getElementById('steps_slider').value;
  let speed = document.getElementById('speed_slider').value;
  let acceleration = document.getElementById('acceleration_slider').value;
  if (acceleration == document.getElementById('acceleration_slider').max) {
    acceleration = 99999999999;       // I know it't terrible, but at least it works
  }
  
  let acceleration_steps = 0.5 * speed * speed / acceleration;
  let acceleration_only = false;
  
  if (acceleration_steps > steps/2) {
    acceleration_steps = steps/2;
    speed = Math.sqrt(2 * acceleration_steps * acceleration);
    acceleration_only = true;
  }
  
  let acceleration_time = (2 * acceleration_steps / speed);
  let total_time = acceleration_time*2 + (steps-(2*acceleration_steps))/speed;
  
//  console.log(acceleration_time, total_time)
  // The time starts from pixels x = 50 and end to pixel x = 550
  // The steps start from y = 300 to y = 50
  
  let first_connection_y = 300-250*(acceleration_steps/steps);
  let first_connection_x = 50+500*acceleration_time/total_time;
  let control_point_time = acceleration_time-acceleration_steps/(acceleration*acceleration_time);
  
  
  
  // Dotted lines and reference value
  drawText(ctx, "Steps", 12, 15, 30);
  drawLine(ctx, 50, 50, 550, 50, '#555', 2, [10, 5]);                                                   // Horizzontal lines
  drawText(ctx, steps, 12, 15, 50);
  drawLine(ctx, 50, first_connection_y, first_connection_x, first_connection_y, '#555', 2, [10, 5]);
  drawText(ctx, Math.round(acceleration_steps), 12, 15, first_connection_y+12);
  
  drawText(ctx, "t [s]", 12, 590, 320);
  drawLine(ctx, 550, 50, 550, 300, '#555', 2, [10, 5]);                                                   // Vertical lines
  drawText(ctx, Math.round(total_time*100)/100, 12, 550, 315);
  drawLine(ctx, first_connection_x, first_connection_y, first_connection_x, 300, '#555', 2, [10, 5]);
  drawText(ctx, Math.round(acceleration_time*100)/100, 12, first_connection_x-20, 315);
  if (!acceleration_only) {
    drawLine(ctx, 50, 350-first_connection_y, 50+(550-first_connection_x), 350-first_connection_y, '#555', 2, [10, 5]);  // Horizzontal lines
    drawText(ctx, Math.round(steps-acceleration_steps), 12, 15, 350-first_connection_y);
    drawLine(ctx, 50+(550-first_connection_x), 350-first_connection_y, 50+(550-first_connection_x), 300, '#555', 2, [10, 5]);  // Vertical lines
    drawText(ctx, Math.round((total_time-acceleration_time)*100)/100, 12, 50+(550-first_connection_x), 315);
  }
  
  ctx.setLineDash([]);
  ctx.lineWidth = 3;
  ctx.strokeStyle = "#f00";
  ctx.beginPath();
  ctx.moveTo(50, 300);
  ctx.quadraticCurveTo(50+500*control_point_time/total_time, 300, first_connection_x, first_connection_y);
  ctx.stroke();
  
//  drawCircle(ctx, 50+500*control_point_time/total_time, 300, 10, '#f00');
  
  drawLine(ctx, first_connection_x, first_connection_y, 600-first_connection_x, 350-first_connection_y, '#00f', 3);
  
  ctx.lineWidth = 3;
  ctx.strokeStyle = "#f00";
  ctx.beginPath();
  ctx.moveTo(550-(first_connection_x-50), 50+(300-first_connection_y));
  ctx.quadraticCurveTo(550-500*(control_point_time)/total_time, 50, 550, 50);
  ctx.stroke();
  
  
  
  // Speed graph
  // The time starts from pixels x = 50 and end to pixel x = 550
  // The steps start from y = 600 to y = 370
  
  // Dotted lines and reference value
  drawText(ctx, "Speed", 12, 5, 330);
  drawText(ctx, "[steps/s]", 11, 1, 345);
  drawLine(ctx, 50, 370, first_connection_x, 370, '#555', 2, [10, 5]);                                                   // Horizzontal lines
  
  drawText(ctx, "t [s]", 12, 590, 620);
  drawLine(ctx, 550, 50, 550, 300, '#555', 2, [10, 5]);                                                   // Vertical lines
  drawText(ctx, Math.round(total_time*100)/100, 12, 550, 315);
  drawLine(ctx, first_connection_x, first_connection_y, first_connection_x, 300, '#555', 2, [10, 5]);
  drawText(ctx, Math.round(acceleration_time*100)/100, 12, first_connection_x-20, 315);
  if (!acceleration_only) {
    drawLine(ctx, 50, 350-first_connection_y, 50+(550-first_connection_x), 350-first_connection_y, '#555', 2, [10, 5]);  // Horizzontal lines
    drawText(ctx, Math.round(steps-acceleration_steps), 12, 15, 350-first_connection_y);
    drawLine(ctx, 50+(550-first_connection_x), 350-first_connection_y, 50+(550-first_connection_x), 300, '#555', 2, [10, 5]);  // Vertical lines
    drawText(ctx, Math.round((total_time-acceleration_time)*100)/100, 12, 50+(550-first_connection_x), 315);
  }
  
  
  drawLine(ctx, 50, 600, first_connection_x, 370, '#f00', 3);
  drawLine(ctx, first_connection_x, 370, 600-first_connection_x, 370, '#00f', 3);
  drawLine(ctx, 600-first_connection_x, 370, 550, 600, '#f00', 3);
  
}

function toggle_enable () {
  if (motors_enabled) {
    motors_enabled = false;
    document.getElementById('toggle_enable_button').className = '';
    document.getElementById('toggle_enable_button').innerText = 'Enable Motors';
  } else {
    motors_enabled = true;
    document.getElementById('toggle_enable_button').className = 'button_red';
    document.getElementById('toggle_enable_button').innerText = 'Disable Motors';
  }
  ajax("/disableStepper?val="+Number(!motors_enabled), () => {});
}

update_plot();
