const gauge = {x:1100, y:300, r:160, width:40, angle_ref:Math.PI/6, background_color:'#ccc', min:15, max:30};
const chart = {origin_x:50, origin_y:550, y_max:30, y_min:10, y_div:10, x_div:10};

let up_temp = true;
let loop_demo = false;
let temperature = (gauge.min + gauge.max)/2;
let temperature_array = [];

document.body.addEventListener("keydown", event => {
  if (event.key === 'd') {
    loop_demo = !loop_demo;
    loop_demo_animation();
    return;
  }
  console.log(event)
  if (event.key === 'r') {
    prg_temperature(temperature);
    temperature_chart();
    return;
  }
});

function temperature_chart (t = undefined) {
  if (t != undefined && t > chart.y_min && t < chart.y_max) {
    temperature_array.push([new Date().getTime(), t]);
    temperature = t;
  }
  
  let canvas = document.getElementById('canvas_temperature_chart');
  let ctx = canvas.getContext('2d');
  
  ctx.clearRect(0, 0, canvas.width, canvas.height);
  
  /**************************** Gauge ***************************/
  // Background
  ctx.lineWidth = gauge.width;
  ctx.beginPath();
  ctx.arc(gauge.x, gauge.y, gauge.r, Math.PI - gauge.angle_ref, gauge.angle_ref);
  ctx.strokeStyle = gauge.background_color;
  ctx.stroke();
  
  // Background right extreme
  ctx.lineWidth = 1;
  ctx.beginPath()
  ctx.arc(gauge.x + gauge.r*Math.cos(gauge.angle_ref), gauge.y + gauge.r*Math.sin(gauge.angle_ref), gauge.width/2, gauge.angle_ref-0.05, Math.PI + gauge.angle_ref + 0.05);
  ctx.fillStyle = gauge.background_color;
  ctx.fill();
  
  // Temperature text
  ctx.font = "Bold 75px Arial";
  ctx.textAlign="center"; 
  ctx.textBaseline = "middle";
  ctx.fillStyle = "#000";
  ctx.fillText(temperature.toFixed(1) + ' °C', gauge.x, gauge.y);
  
  
  // Gauge fill

  let fill_angle = (Math.PI + 2 * gauge.angle_ref) / (gauge.max - gauge.min) * (temperature - gauge.min);
  let rgb_val = interpolateColors(temperature, [{val:gauge.min, color:[0, 255, 0]}, {val:(gauge.max+gauge.min)/2, color:[255, 255, 0]}, {val:gauge.max, color:[255, 0, 0]}])
  let color = rgb(rgb_val = rgb_val);
//  console.log(color);
  
  if (temperature > gauge.max) {
    fill_angle = Math.PI + 2 * gauge.angle_ref;
    color = '#f00';
    /*
    // Background right extreme
    ctx.lineWidth = 1;
    ctx.beginPath()
    ctx.arc(gauge.x + gauge.r*Math.cos(gauge.angle_ref), gauge.y + gauge.r*Math.sin(gauge.angle_ref), gauge.width/2, gauge.angle_ref-0.05, Math.PI + gauge.angle_ref + 0.05);
    ctx.fillStyle = color;
    ctx.fill();
    */
  } else if (temperature < gauge.min) {
    fill_angle = 0;
    color = '#0f0';
  }
  
  ctx.strokeStyle = color;
  ctx.fillStyle = color;
  
  // Left extreme fill color
  ctx.beginPath()
  ctx.arc(gauge.x - gauge.r*Math.cos(gauge.angle_ref), gauge.y + gauge.r*Math.sin(gauge.angle_ref), gauge.width/2, -gauge.angle_ref, Math.PI - gauge.angle_ref);
  ctx.fill();
  
  // Fill proportional to temperature
  ctx.lineWidth = gauge.width;
  ctx.beginPath();
  ctx.arc(gauge.x, gauge.y, gauge.r, Math.PI - gauge.angle_ref, Math.PI - gauge.angle_ref + fill_angle);
  ctx.stroke();
  
  // Right extreme fill color
  ctx.beginPath()
  ctx.arc(gauge.x + gauge.r*Math.cos(Math.PI - gauge.angle_ref + fill_angle), gauge.y + gauge.r*Math.sin(Math.PI - gauge.angle_ref + fill_angle), gauge.width/2, 0, 2 * Math.PI);
  ctx.fill();
  
  
  /*************************** Time chart ******************************/
  // Origin (chart.x, chart.y)
  const y_max_pos = 30;
  const x_max_pos = gauge.x-gauge.r-gauge.width;
  drawLine(ctx, chart.origin_x, y_max_pos, chart.origin_x, chart.origin_y, '#000');       // Y axis
  drawLine(ctx, chart.origin_x, chart.origin_y, x_max_pos, chart.origin_y, '#000');     // X axis
  drawLine(ctx, chart.origin_x-5, y_max_pos+10, chart.origin_x, y_max_pos, '#000');        // Y axis arrow
  drawLine(ctx, chart.origin_x+5, y_max_pos+10, chart.origin_x, y_max_pos, '#000');
  drawLine(ctx, x_max_pos-10, chart.origin_y-5, x_max_pos, chart.origin_y, '#000');    // X axis arrow
  drawLine(ctx, x_max_pos-10, chart.origin_y+5, x_max_pos, chart.origin_y, '#000');
  
  // Dotted division line
  let x_q = (x_max_pos-chart.origin_x)/(chart.x_div+1);
  let y_q = (chart.origin_y-y_max_pos)/(chart.y_div+1);
  for (let i = 1; i <= chart.x_div; i++) {
    drawLine(ctx, chart.origin_x+i*x_q, y_max_pos+y_q, chart.origin_x+i*x_q, chart.origin_y, '#ccc', 2, [10, 5]);                // Dotted vertical lines
  }
  for (let i = 1; i <= chart.y_div; i++) {
    drawLine(ctx, chart.origin_x, y_max_pos+i*y_q, x_max_pos-x_q, y_max_pos+i*y_q, '#ccc', 2, [10, 5]);                         // Dotted horizontal lines
  }
  
  // Actual line chart
  let time = new Date().getTime();
  ctx.save();
  ctx.strokeStyle = '#00f';
  ctx.lineWidth = 3;
  ctx.lineCap = "round";
  ctx.beginPath();
  
  let first_point = true

  for (let point of temperature_array) {
    if (time-point[0] < 1000*60*chart.x_div) {
      if (first_point) {
        ctx.moveTo(chart.origin_x+chart.x_div*x_q-(time-point[0])/1000/60*x_q, chart.origin_y-(point[1]-chart.y_min)/(chart.y_max-chart.y_min)*y_q*chart.y_div);
        first_point = false;
      } else {
        ctx.lineTo(chart.origin_x+chart.x_div*x_q-(time-point[0])/1000/60*x_q, chart.origin_y-(point[1]-chart.y_min)/(chart.y_max-chart.y_min)*y_q*chart.y_div);
      }
    }
  }
  ctx.stroke();
  ctx.restore();
  
  // Labels
  ctx.textAlign="center"; 
  ctx.fillStyle = "#000";
  drawText(ctx, 't [min]', 15, x_max_pos, chart.origin_y+15);
  for (let i = 1; i <= chart.x_div; i++) {
    drawText(ctx, -(chart.x_div-i), 15, chart.origin_x+i*x_q, chart.origin_y+15);
  }
  ctx.textAlign = "right";
  drawText(ctx, 'T [°C]', 15, chart.origin_x-10, y_max_pos+10);
  for (let i = 1; i <= chart.y_div; i++) {
    drawText(ctx, chart.y_min+(chart.y_div-i+1)*(chart.y_max-chart.y_min)/chart.y_div, 15, chart.origin_x-10, y_max_pos+i*y_q);
  }
}

function prg_temperature (t) {
  let time = new Date().getTime();
  const c = 100;
  temperature_array = [];
  temperature = t;
  for (let i = 0; i <= c; i++) {
    t += (Math.random()-0.55);
    temperature_array.push([time-i*(chart.x_div)/(c)*1000*60, t]);
  }
  temperature_array.reverse();
}


function loop_demo_animation() {
  if (loop_demo) {
    if (temperature >= gauge.max + 0.2) {
      up_temp = false;
    } else if (temperature <= gauge.min - 0.2) {
      up_temp = true;
    }
    
    if (up_temp) {
      temperature += 0.035
    } else {
      temperature -= 0.035;
    }
    
    temperature_chart(temperature);
    setTimeout(loop_demo_animation, 30);
  }
}

if (!block_ajax) {
  ajax('/getTemperature', (e) => {
    temperature_chart(Number(e.responseText));
    prg_temperature(temperature);
  });
}

setInterval(() => {
  if (!loop_demo && !block_ajax) {
    ajax('/getTemperature', (e) => {
      temperature_chart(Number(e.responseText));
    });
  }
}, 3000);

setInterval(temperature_chart, 300);
