let root = document.documentElement;

function ajax (url_request, callback) {
  if (window.XMLHttpRequest) {
    request = new XMLHttpRequest();
  } else if (window.ActiveXObject) {
    request = new ActiveXObject("Microsoft.XMLHTTP");
  }
  request.onreadystatechange = function() {
    if (this.readyState == 4 && this.status == 200) {
      callback(this);
    }
  };
  request.open("GET", url_request, true);
  request.setRequestHeader('Content-Type', 'application/x-www-form-urlencoded');
  request.send();
}


function drawLine(ctx, startX, startY, endX, endY, color, lineWidth = 1, dash=[]) {
  ctx.save();
  if (dash) {
    ctx.setLineDash(dash)
  }
  ctx.strokeStyle = color;
  ctx.lineWidth = lineWidth;
  ctx.beginPath();
  ctx.moveTo(startX,startY);
  ctx.lineTo(endX,endY);
  ctx.stroke();
  ctx.restore();
}

function drawCircle(ctx, x, y, radius, fill, stroke, strokeWidth, lineWidth = 1) {
  ctx.lineWidth = lineWidth;
  ctx.beginPath()
  ctx.arc(x, y, radius, 0, 2 * Math.PI, false)
  if (fill) {
    ctx.fillStyle = fill
    ctx.fill()
  }
  if (stroke) {
    ctx.lineWidth = strokeWidth
    ctx.strokeStyle = stroke
    ctx.stroke()
  }
}

function drawText(ctx, text, size, x, y) {
  ctx.font = size + "px Arial";
  ctx.fillText(text, x, y);
}

function rgb(rgb_val) {
  let r = rgb_val[0];
  let g = rgb_val[1];
  let b = rgb_val[2];
  return "#"+(r).toString(16).padStart(2,'0')+(g).toString(16).padStart(2,'0')+(b).toString(16).padStart(2,'0');
}

function interpolateColors(value, points) {
  let x_min, x_max, y_min, y_max;
  for (let point of points) {
//    console.log(point)
    if (value == point.val) {
      return point.color;
    }
    if (value < point.val && x_min != undefined) {
      x_max = point.val;
      y_max = point.color;
      break;
    }
    if (value > point.val) {
      x_min = point.val;
      y_min = point.color;
    }
  }
//  console.log(x_min, x_max, y_min, y_max)
  let result = [0, 0, 0];
  
  if (x_min != undefined && x_max != undefined) {
    for (let i = 0; i < 3; i++) {
      result[i] = Math.round((y_max[i] - y_min[i])/(x_max - x_min) * (value - x_min) + y_min[i]);
//      console.log(value, result[i])
    }
  }
  
  return result;
}
