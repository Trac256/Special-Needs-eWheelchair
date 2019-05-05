<?php
  $code = $_POST['code'];
  switch ($code) {
  case "right":
    system("sudo /home/pi/rover/rr.sh");
    break;
  case "front":
    system("sudo  /home/pi/rover/fwd.sh");
    break;
  case "back":
    system("sudo  /home/pi/rover/rwd.sh");
    break;
  case "left":
    system("sudo /home/pi/rover/ll.sh");
    break;
  case "stop":
    system("sudo /home/pi/rover/stop.sh");
    break;
  default:
  }

?>
