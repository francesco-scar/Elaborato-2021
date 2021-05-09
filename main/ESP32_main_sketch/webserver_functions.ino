String getContentType(String filename) {
  if (server.hasArg("download")) {
    return "application/octet-stream";
  } else if (filename.endsWith(".htm")) {
    return "text/html";
  } else if (filename.endsWith(".html")) {
    return "text/html";
  } else if (filename.endsWith(".css")) {
    return "text/css";
  } else if (filename.endsWith(".js")) {
    return "application/javascript";
  } else if (filename.endsWith(".png")) {
    return "image/png";
  } else if (filename.endsWith(".gif")) {
    return "image/gif";
  } else if (filename.endsWith(".jpg")) {
    return "image/jpeg";
  } else if (filename.endsWith(".ico")) {
    return "image/x-icon";
  } else if (filename.endsWith(".xml")) {
    return "text/xml";
  } else if (filename.endsWith(".pdf")) {
    return "application/x-pdf";
  } else if (filename.endsWith(".zip")) {
    return "application/x-zip";
  } else if (filename.endsWith(".gz")) {
    return "application/x-gzip";
  }
  return "text/plain";
}



bool exists(String path) {
  bool yes = false;
  File file = SPIFFS.open(path, "r");
  if (!file.isDirectory()) {
    yes = true;
  }
  file.close();
  return yes;
}


bool handleFileRead(String path) {
  Serial.println("handleFileRead: " + path);
  if (path.endsWith("/")) {
    path += "index.html";
  }
  String contentType = getContentType(path);
  String pathWithGz = path + ".gz";
  if (exists(pathWithGz) || exists(path)) {
    if (exists(pathWithGz)) {
      path += ".gz";
    }
    File file = SPIFFS.open(path, "r");
    server.streamFile(file, contentType);
    file.close();
    return true;
  }
  return false;
}


void imageMatrixRequest () {
  if (server.hasArg("scanBefore")) {
    #ifndef DEFAULT_MATRIX_TEST
      getImageMatrix();
    #endif
  }
  String output_matrix = "";
  for (uint16_t i = 0; i < 18 * 18; i++) {
    output_matrix += String(matrix[i / 18][i % 18]);
    if (i != 18 * 18 - 1) {
      output_matrix += ",";
    }
  }
  clear_matrix_val();
  bool valid_image = circle_border();

  String output_gradient = "";
  for (uint16_t i = 0; i < 16 * 16; i++) {
    output_gradient += String(gradient_modules[i / 16][i % 16] * valid_image);
    if (i != 16 * 16 - 1) {
      output_gradient += ",";
    }
  }

  gradient_descent(7, 8.5, 1, 256);
  
  String output_progressive = "";
  for (uint16_t i = 0; i < 256*3; i++) {
    output_progressive += String(progressive_approximations[i]);
    if (i != 256*3-1) {
      output_progressive += ",";
    }
  }


  server.send(200, "text/plain", "{\"matrix\":[" + output_matrix + "], \"valid_image\":" + valid_image + ", \"gradient\":[" + output_gradient + "], \"progressive_approximations\":[" + output_progressive + "]}");
  if (server.hasArg("scanAfter")) {
    getImageMatrix();
  }
}
