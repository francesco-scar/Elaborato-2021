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
  if (dash) {
    ctx.setLineDash(dash)
  }
  ctx.strokeStyle = color;
  ctx.lineWidth = lineWidth;
  ctx.beginPath();
  ctx.moveTo(startX,startY);
  ctx.lineTo(endX,endY);
  ctx.stroke();
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
