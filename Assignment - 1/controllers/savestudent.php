<?php
	include_once("../controllers/common.php");
	include_once("../models/student.php");
	Database::connect();
	$id = safeGet("id", 0);
	if($id==0) {
		$name = safeGet("name");
		Student::add($name);
	} else {
		$student = new Student($id);
		$student->name = safeGet("name");
		$student->save();
	}
	header('Location: ../students.php');
?>