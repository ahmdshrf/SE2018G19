<?php
	include_once("../controllers/common.php");
	include_once("../models/grade.php");
	Database::connect();
	$id = safeGet("id", 0);
	if($id==0) {
		$student_id = safeGet("student_id");
		$course_id = safeGet("course_id");
        $degree = safeGet("degree");
        $examine_at = safeGet("examine_at");
		Grade::add($student_id,$course_id,$degree,$examine_at);
	} else {
		$grade = new Grade($id);
		$grade->degree= safeGet("degree");
		$grade->student_id = safeGet("student_id");
	    $grade->course_id = safeGet("course_id");
		$grade->examine_at = safeGet("examine_at");

		$grade->save();
	}
	
	header('Location: ../grades.php');
?>