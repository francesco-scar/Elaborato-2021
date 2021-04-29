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
}

function move_stepper (motion) {
  let acceleration_value = document.getElementById('acceleration_slider').value;
  if (acceleration_value == document.getElementById('acceleration_slider').max) {
    acceleration_value = 99999999999;       // I know it't terrible, but at least it works
  }
  ajax("/moveStepper?motion="+motion+"&steps="+document.getElementById('steps_slider').value+"&speed="+document.getElementById('speed_slider').value+"&acceleration="+acceleration_value, () => {});
}


function empty_plot () {
  let canvas = document.getElementById('canvas_motor');
  let ctx = canvas.getContext("2d");
  ctx.clearRect(0, 0, canvas.width, canvas.height);
}
