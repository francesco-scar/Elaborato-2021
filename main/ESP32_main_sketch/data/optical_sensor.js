const N_PIXELS = 18;
let last_matrix = new Array(18*18); last_matrix.fill(0);

let coefficient = 100;
let steps = 10;
let max_angle = 60;

let loop = false;
let running_demo = false;
let last_timeout;

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
  if (document.getElementById('display_polar').checked) {
    let canvas = document.getElementById("canvas_image");
    let ctx = canvas.getContext("2d");
      
    for (let angle = steps; angle <= max_angle; angle += steps) {
      drawCircle(ctx, canvas.width/2, canvas.height/2, coefficient*Math.tan(angle*Math.PI/180), '', '#ff0000', 2);
    }
  } else {
    draw_pixels(last_matrix);
  }
}

function draw_center_axis () {
  if (document.getElementById('display_center').checked) {
    let canvas = document.getElementById("canvas_image");
    let ctx = canvas.getContext("2d");
    drawLine(ctx, canvas.width/2, 0, canvas.width/2, canvas.height, '#ff0000');
    drawLine(ctx, 0, canvas.height/2, canvas.width, canvas.height/2, '#ff0000');
  } else {
    draw_pixels(last_matrix);
  }
}



function call_ajax() {
  ajax('/getImageMatrix?scanAfter=1', (e) => {
    let json_response = JSON.parse(e.responseText);
    last_matrix = json_response.matrix
    draw_pixels(last_matrix);
    last_timeout = setTimeout(call_ajax, 1500);
  });
}

function call_ajax_once() {
  ajax('/getImageMatrix?scanAfter=1', (e) => {
    let json_response = JSON.parse(e.responseText);
    last_matrix = json_response.matrix;
    draw_pixels(last_matrix);
  });
}


function toggle_loop () {
  if (loop) {
    loop = false;
    document.getElementById("frame_button").disabled = false;
    document.getElementById("start_button").disabled = false;
    document.getElementById("loop_button").className = '';
    document.getElementById("loop_button").innerText = 'Loop';
    clearTimeout(last_timeout);
  } else {
    loop = true;
    document.getElementById("frame_button").disabled = true;
    document.getElementById("start_button").disabled = true;
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
    document.getElementById("start_button").className = '';
    document.getElementById("start_button").innerText = 'Start';
    clearTimeout(last_timeout);
  } else {
    running_demo = true;
    document.getElementById("frame_button").disabled = true;
    document.getElementById("loop_button").disabled = true;
    document.getElementById("start_button").className = 'button_red';
    document.getElementById("start_button").innerText = 'Stop';
//    call_ajax();
    // TODO
  }
}


function display_threshold () {
  let label = document.getElementById('threshold_label');
  let slider = document.getElementById('threshold_slider');
  let checkbox = document.getElementById('display_threshold');
  
  if (checkbox.checked) {
    slider.disabled = false;
    label.innerText = slider.value;
    let threshold_array = new Array(N_PIXELS**2);
    for (let i = 0; i < N_PIXELS**2; i++) {
      if ((last_matrix[i] & 0b00111111) >= slider.value) {
        threshold_array[i] = 63;
      } else {
        threshold_array[i] = 0;
      }
    }
    draw_pixels(threshold_array);
  } else {
    slider.disabled = true;
    draw_pixels(last_matrix);
  }
}

draw_pixels (last_matrix);
