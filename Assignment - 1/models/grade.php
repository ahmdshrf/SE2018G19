<?php
	include_once('database.php');

	class Grade extends Database{
		function __construct($id) {
			$sql = "SELECT * FROM grades WHERE id = $id;";
			$statement = Database::$db->prepare($sql);
			$statement->execute();
			$data = $statement->fetch(PDO::FETCH_ASSOC);
			if(empty($data)){return;}
			foreach ($data as $key => $value) {
				$this->{$key} = $value;
			}
		}

		
		public static function add($student_id,$course_id,$degree,$examine_at) {
			$sql = "INSERT INTO grades (student_id,course_id,degree,examine_at) VALUES (?,?,?,?)";
			Database::$db->prepare($sql)->execute([$student_id,$course_id,$degree,$examine_at]);
		    
		}
		
		public function delete() {
			$sql = "DELETE FROM grades WHERE id = $this->id;";
			Database::$db->query($sql);
		}

		public function save() {
			
            $sql = "UPDATE grades SET student_id  = ? WHERE id = ?;";
			Database::$db->prepare($sql)->execute([$this->student_id, $this->id]);
		  
		   $sql = "UPDATE grades SET course_id = ? WHERE id = ?;";
			Database::$db->prepare($sql)->execute([$this->course_id, $this->id]);
          
            $sql = "UPDATE grades SET degree = ? WHERE id = ?;";
			Database::$db->prepare($sql)->execute([$this->degree, $this->id]);
		 
           	$sql = "UPDATE grades SET examine_at = ? WHERE id = ?;";
			Database::$db->prepare($sql)->execute([$this->examine_at, $this->id]);
			

		}


		public static function all($keyword) {
			$keyword = str_replace(" ", "%", $keyword);
			$sql = "SELECT * FROM grades;";
			$statement = Database::$db->prepare($sql);
			$statement->execute();
			$grades = [];
			while($row = $statement->fetch(PDO::FETCH_ASSOC)) {
				$grades[] = new Grade($row['id']);
			}
			return $grades;
		}
	}
?>