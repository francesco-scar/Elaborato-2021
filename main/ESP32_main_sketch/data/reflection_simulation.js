let up = true;

function main_reflection_drawing_handler() {
  let canvas = document.getElementById("canvas_reflection");
  let ctx = canvas.getContext("2d");
  let unit = canvas.width/(Number(document.getElementById("base_slider").max) + Number(document.getElementById("mirror_slider").max)*2);
  
  let rays_per_mirror = Number(document.getElementById("rays_slider").value);
  let sun_angle = Number(document.getElementById("sun_angle_slider").value);
  let base = Number(document.getElementById("base_slider").value);
  let mirror = Number(document.getElementById("mirror_slider").value);
  
  const diagonal = Math.sqrt(canvas.height**2 + canvas.width**2);
  
  document.getElementById('rays_label').innerText = rays_per_mirror;
  document.getElementById('sun_angle_label').innerText = sun_angle;
  document.getElementById('base_label').innerText = base;
  document.getElementById('mirror_label').innerText = mirror;
  
  sun_angle = sun_angle*Math.PI/180;              // Convert in radiant
  
  let o1 = 0;
  let o2 = 0;
  
  let min = -1;
  let angle_min;
  
  if (sun_angle != -Math.PI/2) {
    for (o1 = 0.001; o1 <= Math.PI; o1 += 0.001) {
      if (Math.abs(Math.sqrt(mirror**2 + base**2 + 2*mirror*base*Math.cos(o1))*Math.cos(2*o1-sun_angle) + mirror*Math.sin(o1)) < min || min == -1) {
        min = Math.abs(Math.sqrt(mirror**2 + base**2 + 2*mirror*base*Math.cos(o1))*Math.cos(2*o1-sun_angle) + mirror*Math.sin(o1));
        angle_min = o1;
      } else if (min < 0.1) {
        break;
      }
  //    console.log(Math.abs(Math.sqrt(mirror**2 + base**2 + 2*mirror*base*Math.cos(o1))*Math.cos(2*o1-sun_angle) + mirror*Math.sin(o1)));
    }
    o1 = angle_min;
  } else {
    o1 = 0;
  }
    
  if (sun_angle != Math.PI/2) {
    min = -1;
    for (o2 = 0.001; o2 <= Math.PI; o2 += 0.001) {
      if (Math.abs(Math.sqrt(mirror**2 + base**2 + 2*mirror*base*Math.cos(o2))*Math.cos(2*o2+sun_angle) + mirror*Math.sin(o2)) < min || min == -1) {
        min = Math.abs(Math.sqrt(mirror**2 + base**2 + 2*mirror*base*Math.cos(o2))*Math.cos(2*o2+sun_angle) + mirror*Math.sin(o2));
        angle_min = o2;
      } else if (min < 0.1) {
        break;
      }
    }
    o2 = angle_min;
  } else {
    o2 = 0;
  }
  
  document.getElementById("o1").innerText = (o1*180/Math.PI).toFixed(2);
  document.getElementById("o2").innerText = (o2*180/Math.PI).toFixed(2);
  
  ctx.clearRect(0, 0, canvas.width, canvas.height);
  
  drawLine(ctx, (canvas.width-base*unit)/2, canvas.height-30, (canvas.width+base*unit)/2, canvas.height-30, '#0000ff', 3);   // Horizzontal base line
  drawLine(ctx, (canvas.width-base*unit)/2, canvas.height-30, (canvas.width-base*unit)/2-mirror*unit*Math.cos(o1), canvas.height-30-mirror*unit*Math.sin(o1), '#000000', 3);   // Mirror left line
  drawLine(ctx, (canvas.width+base*unit)/2, canvas.height-30, (canvas.width+base*unit)/2+mirror*unit*Math.cos(o2), canvas.height-30-mirror*unit*Math.sin(o2), '#000000', 3);   // Mirror right line
  
  
  // Sun light
  for (let i = 0; i < rays_per_mirror; i++) {
    drawLine(ctx, (canvas.width-base*unit)/2-mirror*unit*Math.cos(o1)*i/(rays_per_mirror-1), canvas.height-30-mirror*unit*Math.sin(o1)*i/(rays_per_mirror-1), (canvas.width-base*unit)/2-mirror*unit*Math.cos(o1)*i/(rays_per_mirror-1) + diagonal*Math.sin(sun_angle), canvas.height-30-mirror*unit*Math.sin(o1)*i/(rays_per_mirror-1) - diagonal*Math.cos(sun_angle), '#ff0000');   // Left mirror rays
    
    drawLine(ctx, (canvas.width+base*unit)/2+mirror*unit*Math.cos(o2)*i/(rays_per_mirror-1), canvas.height-30-mirror*unit*Math.sin(o2)*i/(rays_per_mirror-1), (canvas.width+base*unit)/2+mirror*unit*Math.cos(o2)*i/(rays_per_mirror-1) + diagonal*Math.sin(sun_angle), canvas.height-30-mirror*unit*Math.sin(o2)*i/(rays_per_mirror-1) - diagonal*Math.cos(sun_angle), '#ff0000');   // Right mirror rays
  }
  
  
  // Reflected rays
  for (let i = 0; i < rays_per_mirror; i++) {
    drawLine(ctx, (canvas.width-base*unit)/2-mirror*unit*Math.cos(o1)*i/(rays_per_mirror-1), canvas.height-30-mirror*unit*Math.sin(o1)*i/(rays_per_mirror-1), (canvas.width-base*unit)/2-mirror*unit*Math.cos(o1)*i/(rays_per_mirror-1) + diagonal*Math.sin(sun_angle - 2*o1 + Math.PI), canvas.height-30-mirror*unit*Math.sin(o1)*i/(rays_per_mirror-1) + diagonal*Math.cos(sun_angle - 2*o1 + Math.PI), '#ff0000');   // Left mirror rays
    
    drawLine(ctx, (canvas.width+base*unit)/2+mirror*unit*Math.cos(o2)*i/(rays_per_mirror-1), canvas.height-30-mirror*unit*Math.sin(o2)*i/(rays_per_mirror-1), (canvas.width+base*unit)/2+mirror*unit*Math.cos(o2)*i/(rays_per_mirror-1) - diagonal*Math.sin(- sun_angle - 2*o2 + Math.PI), canvas.height-30-mirror*unit*Math.sin(o2)*i/(rays_per_mirror-1) + diagonal*Math.cos(- sun_angle - 2*o2 + Math.PI), '#ff0000');   // Right mirror rays
  }
  
  ctx.clearRect(0, canvas.height-29, canvas.width, canvas.height);
  if (o1 > Math.PI/4) {
    ctx.clearRect(0, canvas.height-31, (canvas.width-base*unit)/2-1, canvas.height);
  }
  if (o2 > Math.PI/4) {
    ctx.clearRect((canvas.width+base*unit)/2+1, canvas.height-31, canvas.width, canvas.height);
  }
  
//  drawCircle(ctx, (canvas.width-base*unit)/2-mirror*unit*Math.cos(o1), canvas.height-30-mirror*unit*Math.sin(o1), (base+mirror)*unit, '', '#00ff00', 2);
//  drawCircle(ctx, (canvas.width+base*unit)/2, canvas.height-30, mirror*unit, '', '#00ff00', 2);
}



function loop_sun_angle_animation() {
  if (document.getElementById("loop_sun_angle_animation").checked) {
    if (document.getElementById("sun_angle_slider").value >= 90) {
      up = false;
    } else if (document.getElementById("sun_angle_slider").value <= -90) {
      up = true;
    }
    
    if (up) {
      document.getElementById("sun_angle_slider").value = Number(document.getElementById("sun_angle_slider").value) + 1;
    } else {
      document.getElementById("sun_angle_slider").value = Number(document.getElementById("sun_angle_slider").value) - 1;
    }
    
    main_reflection_drawing_handler();
    setTimeout(loop_sun_angle_animation, 50);
  }
}


main_reflection_drawing_handler();
