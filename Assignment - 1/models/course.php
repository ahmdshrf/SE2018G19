<?php
	include_once('database.php');

	class Course extends Database{
		function __construct($id) {
			$sql = "SELECT * FROM courses WHERE id = $id;";
			$statement = Database::$db->prepare($sql);
			$statement->execute();
			$data = $statement->fetch(PDO::FETCH_ASSOC);
			if(empty($data)){return;}
			foreach ($data as $key => $value) {
				$this->{$key} = $value;
			}
		}

		public static function add($name,$max_degree,$study_year) {
			$sql = "INSERT INTO courses (name,max_degree,study_year) VALUES (?,?,?)";
			Database::$db->prepare($sql)->execute([$name,$max_degree,$study_year]);
		    
		}
		
		public function delete() {
			$sql = "DELETE FROM courses WHERE id = $this->id;";
			Database::$db->query($sql);
		}

		public function save() {
			$sql = "UPDATE courses SET name = ? WHERE id = ?;";
			Database::$db->prepare($sql)->execute([$this->name, $this->id]);
		
            $sql = "UPDATE courses SET max_degree = ? WHERE id = ?;";
			Database::$db->prepare($sql)->execute([$this->max_degree, $this->id]);
		  
		   $sql = "UPDATE courses SET study_year = ? WHERE id = ?;";
			Database::$db->prepare($sql)->execute([$this->study_year, $this->id]);
		

		}
        public static function get_course($id){
			$id = str_replace(" ", "%", $id);
			$sql = "SELECT * FROM courses WHERE id like ('$id');";
			$statement = Database::$db->prepare($sql);
			$statement->execute();
			$courses = [];
			while($row = $statement->fetch(PDO::FETCH_ASSOC)) {
				$courses[] = new Course($row['id']);
			}
			return $courses[0];
		}

		public static function all($keyword) {
			$keyword = str_replace(" ", "%", $keyword);
			$sql = "SELECT * FROM courses WHERE name like ('%$keyword%');";
			$statement = Database::$db->prepare($sql);
			$statement->execute();
			$courses = [];
			while($row = $statement->fetch(PDO::FETCH_ASSOC)) {
				$courses[] = new Course($row['id']);
			}
			return $courses;
		}
	}
?>