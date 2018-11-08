<?php
	include_once("../controllers/common.php");
	include_once("../models/course.php");
	Database::connect();
	
	$id = safeGet("id", 0);
	if($id==0) {
		$name = safeGet("name");
	    $max_degree = safeGet("max_degree");
		$study_year = safeGet("study_year");

		Course::add($name,$max_degree,$study_year);
	} else {
	
		$course = new Course($id);
		$course->name = safeGet("name");
	    $course->max_degree = safeGet("max_degree");
		$course->study_year = safeGet("study_year");
		$course->save();
	}
	header('Location: ../courses.php');
?>