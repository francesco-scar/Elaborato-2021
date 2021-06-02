const gauge = {x:1100, y:300, r:160, width:40, angle_ref:Math.PI/6, background_color:'#ccc', min:15, max:30};
let up_temp = true;
let loop_demo = false;
let temperature = (gauge.min + gauge.max)/2;

document.body.addEventListener("keydown", event => {
  if (event.keyCode === 68) { // 68 is keycode for 'd'
    loop_demo = !loop_demo;
    loop_demo_animation();
    return;
  }
});

function temperature_chart (t) {
  let canvas = document.getElementById('canvas_temperature_chart');
  let ctx = canvas.getContext('2d');
  
  ctx.clearRect(0, 0, canvas.width, canvas.height);
  
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
  ctx.fillText(t.toFixed(1) + ' °C', gauge.x, gauge.y);
  
  
  // Gauge fill

  let fill_angle = (Math.PI + 2 * gauge.angle_ref) / (gauge.max - gauge.min) * (t - gauge.min);
  let rgb_val = interpolateColors(t, [{val:gauge.min, color:[0, 255, 0]}, {val:(gauge.max+gauge.min)/2, color:[255, 255, 0]}, {val:gauge.max, color:[255, 0, 0]}])
  let color = rgb(rgb_val = rgb_val);
//  console.log(color);
  
  if (t > gauge.max) {
    fill_angle = Math.PI + 2 * gauge.angle_ref;
    color = '#f00';
    
    // Background right extreme
    ctx.lineWidth = 1;
    ctx.beginPath()
    ctx.arc(gauge.x + gauge.r*Math.cos(gauge.angle_ref), gauge.y + gauge.r*Math.sin(gauge.angle_ref), gauge.width/2, gauge.angle_ref-0.05, Math.PI + gauge.angle_ref + 0.05);
    ctx.fillStyle = color;
    ctx.fill();
  } else if (t < gauge.min) {
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
}


function loop_demo_animation() {
  if (loop_demo) {
    if (temperature >= gauge.max + 0.2) {
      up_temp = false;
    } else if (temperature <= gauge.min - 0.2) {
      up_temp = true;
    }
    
    if (up_temp) {
      temperature += 0.1
    } else {
      temperature -= 0.1;
    }
    
    temperature_chart(temperature);
    setTimeout(loop_demo_animation, 50);
  }
}
