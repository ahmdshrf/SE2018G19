<?php
	include_once('database.php');

	class Student extends Database{
		function __construct($id) {
			$sql = "SELECT * FROM students WHERE id = $id;";
			$statement = Database::$db->prepare($sql);
			$statement->execute();
			$data = $statement->fetch(PDO::FETCH_ASSOC);
			if(empty($data)){return;}
			foreach ($data as $key => $value) {
				$this->{$key} = $value;
			}
		}

		public static function add($name) {
			$sql = "INSERT INTO students (name) VALUES (?)";
			Database::$db->prepare($sql)->execute([$name]);
		}
		
		public function delete() {
			$sql = "DELETE FROM students WHERE id = $this->id;";
			Database::$db->query($sql);
		}

		public function save() {
			$sql = "UPDATE students SET name = ? WHERE id = ?;";
			Database::$db->prepare($sql)->execute([$this->name, $this->id]);
		}

		public static function get_student($id) {
			$id = str_replace(" ", "%", $id);
			$sql = "SELECT * FROM students WHERE id like ('$id');";
			$statement = Database::$db->prepare($sql);
			$statement->execute();
			$students = [];
			while($row = $statement->fetch(PDO::FETCH_ASSOC)) {
				$students[] = new Student($row['id']);
			}
			return $students[0];
		}

		public static function all($keyword) {
			$keyword = str_replace(" ", "%", $keyword);
			$sql = "SELECT * FROM students WHERE name like ('%$keyword%');";
			$statement = Database::$db->prepare($sql);
			$statement->execute();
			$students = [];
			while($row = $statement->fetch(PDO::FETCH_ASSOC)) {
				$students[] = new Student($row['id']);
			}
			return $students;
		}
	}
?>