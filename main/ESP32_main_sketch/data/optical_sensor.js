const N_PIXELS = 18;
let last_matrix = new Array(18*18); last_matrix.fill(0);
let last_gradient = new Array(16*16); last_gradient.fill(0);
let progressive_approximations = new Array(512); progressive_approximations.fill([255, 255, 255]);
valid_image = false;

let coefficient = 42;
let steps = 5;
let max_angle = 25;

let loop = false;
let running_demo = false;
let last_timeout;
let last_animation_interval;





function call_ajax() {
  ajax('/getImageMatrix?scanAfter=1', (e) => {
    let json_response = JSON.parse(e.responseText);
    last_matrix = json_response.matrix;
    last_gradient = json_response.gradient;
    valid_image = json_response.valid_image;
    progressive_approximations = json_response.progressive_approximations;
    main_image_drawing_handler();
    if (loop) {
      last_timeout = setTimeout(call_ajax, 500);
    }
  });
}

function call_ajax_once() {
  ajax('/getImageMatrix?scanBefore=1', (e) => {
    let json_response = JSON.parse(e.responseText);
    last_matrix = json_response.matrix;
    last_gradient = json_response.gradient;
    valid_image = json_response.valid_image;
    progressive_approximations = json_response.progressive_approximations;
    main_image_drawing_handler();
  });
}





function draw_pixels (matrix) {
  let canvas = document.getElementById("canvas_image");
  let pixel_size = canvas.width/N_PIXELS/2;       // Assuming it's a square
  let ctx = canvas.getContext("2d");
  ctx.clearRect(0, 0, canvas.width, canvas.height);
  for (let i = 0; i < N_PIXELS*N_PIXELS; i++) {
    ctx.fillStyle = '#'+(('0'+Math.round((matrix[i]&0b111111)/(2**6-1)*(2**8-1)).toString(16)).slice(-2)).repeat(3);
    ctx.fillRect(pixel_size*(i%N_PIXELS)+pixel_size*N_PIXELS/2, pixel_size*Math.floor(i/N_PIXELS)+pixel_size*N_PIXELS/2, pixel_size-1, pixel_size-1);
  }
  
  if (document.getElementById('display_center').checked) {
    draw_center_axis();
  }
  if (document.getElementById('display_polar').checked) {
    draw_polar_axis();
  }
}

function draw_polar_axis () {
  let canvas = document.getElementById("canvas_image");
  let ctx = canvas.getContext("2d");
  let pixel_size = canvas.width/N_PIXELS/2;
    
  for (let angle = steps; angle <= max_angle; angle += steps) {
    drawCircle(ctx, canvas.width/2, canvas.height/2, coefficient*Math.tan(angle*Math.PI/180)*pixel_size, '', '#ff0000', 2);
  }
}

function draw_center_axis () {
  let canvas = document.getElementById("canvas_image");
  let ctx = canvas.getContext("2d");
  drawLine(ctx, canvas.width/2, 0, canvas.width/2, canvas.height, '#ff0000');
  drawLine(ctx, 0, canvas.height/2, canvas.width, canvas.height/2, '#ff0000');
}


function toggle_loop () {
  if (loop) {
    loop = false;
    document.getElementById("frame_button").disabled = false;
    document.getElementById("loop_button").className = '';
    document.getElementById("loop_button").innerText = 'Loop';
    clearTimeout(last_timeout);
  } else {
    loop = true;
    document.getElementById("frame_button").disabled = true;
    document.getElementById("loop_button").className = 'button_red';
    document.getElementById("loop_button").innerText = 'Stop';
    call_ajax();
  }
}


function toggle_demo() {
  if (running_demo) {
    running_demo = false;
    document.getElementById("frame_button").disabled = false;
    document.getElementById("loop_button").disabled = false;
    clearTimeout(last_timeout);
    // TODO
  } else {
    running_demo = true;
    document.getElementById("frame_button").disabled = true;
    document.getElementById("loop_button").disabled = true;
//    call_ajax();
    // TODO
  }
}


function draw_gradient () {
  let label = document.getElementById('gradient_label');
  let slider = document.getElementById('gradient_slider');

  slider.disabled = false;
  label.innerText = slider.value;
  let gradient_array = new Array(N_PIXELS**2);
  for (let y = 0; y < N_PIXELS-2; y++) {
    for (let x = 0; x < N_PIXELS-2; x++) {
      if (slider.value == 0) {
        gradient_array[(y+1)*N_PIXELS + x + 1] = Math.round((last_gradient[y*(N_PIXELS-2) + x])/Math.SQRT2);
      } else if ((last_gradient[y*(N_PIXELS-2) + x]) >= slider.value) {
        gradient_array[(y+1)*N_PIXELS + x + 1] = 63;
      } else {
        gradient_array[(y+1)*N_PIXELS + x + 1] = 0;
      }
    }
  }
  draw_pixels(gradient_array);
}


function display_sun_center() {
  let slider = document.getElementById('sun_center_slider');
  let loop_label = document.getElementById('sun_center_loop_span_label');
  let animation_checkbox = document.getElementById('loop_sun_center_animation');
  if (document.getElementById('display_sun_center').checked && valid_image) {
    slider.disabled = false;
    let slider_val = slider.value;
    document.getElementById('sun_center_label').innerText = slider_val;
    let canvas = document.getElementById("canvas_image");
    let ctx = canvas.getContext("2d");
    let pixel_size = canvas.width/N_PIXELS/2;       // Assuming it's a square
    drawCircle(ctx, canvas.width/2 + progressive_approximations[3*slider_val]*pixel_size, canvas.height/2 + progressive_approximations[3*slider_val+1]*pixel_size, progressive_approximations[3*slider_val+2]*pixel_size, '', '#00ff00', 3);
    drawCircle(ctx, canvas.width/2 + progressive_approximations[3*slider_val]*pixel_size, canvas.height/2 + progressive_approximations[3*slider_val+1]*pixel_size, 4, '#00ff00', '#00ff00', 3);
    loop_label.className = '';
    document.getElementById('animation_loop_cycle').disabled = false;
    animation_checkbox.disabled = false;
    document.getElementById('azimut').innerText = ((Math.atan(progressive_approximations[3*slider_val+1]/progressive_approximations[3*slider_val])*180/Math.PI) + (progressive_approximations[3*slider_val] < 0 ? 270 : 90)).toFixed(1);
    document.getElementById('elevation').innerText = Number.parseFloat(Math.atan(Math.sqrt(progressive_approximations[3*slider_val]**2 + progressive_approximations[3*slider_val+1]**2)/coefficient)*180/Math.PI).toFixed(1);
  } else {
    slider.disabled = true;
    loop_label.className = 'disabled';
    document.getElementById('animation_loop_cycle').disabled = true;
    animation_checkbox.disabled = true;
    document.getElementById('azimut').innerText = '0.0';
    document.getElementById('elevation').innerText = '0.0';
    clearInterval(last_animation_interval);
  }
}

function loop_sun_center_animation() {
  if (document.getElementById('loop_sun_center_animation').checked && document.getElementById('display_sun_center').checked) {
    last_animation_interval = setInterval(() => {
      document.getElementById('sun_center_slider').value = (Number(document.getElementById('sun_center_slider').value) + 1 ) % Number(document.getElementById('animation_loop_cycle').value);
      document.getElementById('sun_center_label').innerText = document.getElementById('sun_center_slider').value;
      main_image_drawing_handler();
    }, 50);
    document.getElementById('animation_loop_cycle').disabled = false;
  } else {
    clearInterval(last_animation_interval);
    document.getElementById('animation_loop_cycle').disabled = true;
  }
}



function main_image_drawing_handler() {
  document.getElementById('sun_center_slider').max = Number(progressive_approximations.length)/3 - 1;
  
  if (document.getElementById('display_gradient').checked) {
    draw_gradient();
  } else {
    document.getElementById('gradient_slider').disabled = true;
    draw_pixels(last_matrix);
  }
  
  
  if (document.getElementById('display_polar').checked) {
    draw_polar_axis();
  }
  
  if (document.getElementById('display_center').checked) {
    draw_center_axis();
  }
  
  display_sun_center();
}

draw_pixels (last_matrix);
