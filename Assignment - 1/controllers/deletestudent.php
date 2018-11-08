<?php
	header('Content-Type: application/json; charset=utf-8');
	include_once("../models/student.php");
	Database::connect();
	$student = new Student($_GET['id']);
	$student->delete();
	echo json_encode(['status'=>1]);
?>