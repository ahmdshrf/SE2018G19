<?php
	class Database {
		protected static $db = null;
		
              public static function connect() {
			if(!empty(Database::$db)) return;

			$dsn = "mysql:host=sql203.epizy.com;dbname=epiz_22955017_school";
			$uid=epiz_22955017;
			$pwd=afCr7Ei5In;
			try {
		   		Database::$db = new PDO($dsn, $uid, $pwd);
			} catch(PDOException $e){
		   		echo $e->getMessage();
			}
		}
		public function get($field) {
			if(isset($this->{$field}))
				return $this->{$field};
			return null;
		}
	}
?>