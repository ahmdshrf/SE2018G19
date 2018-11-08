<?php
  function safeGet($name, $default = null){
    return (isset($_REQUEST[$name]))?$_REQUEST[$name]:$default;
  }
?>