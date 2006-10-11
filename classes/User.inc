<?php
/**
* @copyright Copyright (C) 2006 City of Bloomington, Indiana. All rights reserved.
* @license http://www.gnu.org/copyleft/gpl.html GNU/GPL, see LICENSE.txt
* This file is part of the City of Bloomington's web application Scaffolding.
* This Scaffolding is free software; you can redistribute it and/or modify
* it under the terms of the GNU General Public License as published by
* the Free Software Foundation; either version 2 of the License, or
* (at your option) any later version.
*
* This Scaffolding is distributed in the hope that it will be useful,
* but WITHOUT ANY WARRANTY; without even the implied warranty of
* MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
* GNU General Public License for more details.
*
* You should have received a copy of the GNU General Public License
* along with this scaffolding; if not, write to the Free Software
* Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301, USA
*/
	class User extends SystemUser
	{
		private $id;
		private $username;
		private $password;
		private $authenticationMethod;

		private $firstname;
		private $lastname;

		private $roles;

		public function __construct($id = null)
		{
			global $PDO;

			if ($id)
			{
				# Load an existing user
				if (is_numeric($id)) { $sql = "select * from users where id=$id"; }
				else { $sql = "select * from users where username='$id'"; }

				$result = $PDO->query($sql);
				if ($user = $result->fetch())
				{
					$this->id = $user['id'];
					$this->username = $user['username'];
					# Passwords are one-way encrypted.  They should not be loaded by default
					$this->authenticationMethod = $user['authenticationMethod'];

					$this->firstname = $user['firstname'];
					$this->lastname = $user['lastname'];

					$result->closeCursor();
				}
				else { throw new Exception("unknownUser"); }
			}
		}

		public function save()
		{
			# Check for required fields before saving
			if (!$this->username || !$this->firstname || !$this->lastname) { throw new Exception("missingRequiredFields"); }

			$fields = array();
			$fields[] = "username='{$this->username}'";
			$fields[] = "firstname='{$this->firstname}'";
			$fields[] = "lastname='{$this->lastname}'";
			if ($this->authenticationMethod) { $fields[] = "authenticationMethod='{$this->authenticationMethod}'"; } else { $fields[] = "authenticationMethod=null"; }
			$fields = implode(",",$fields);

			if ($this->id) { $this->update($fields); }
			else { $this->insert($fields); }

			$this->updateRoles();
		}

		public function delete()
		{
			global $PDO;

			$PDO->beginTransaction();

			$sql = "delete from user_roles where user_id={$this->id}";
			if (false === $PDO->exec($sql)) { $e = $PDO->errorInfo(); $PDO->rollBack(); throw new Exception($sql.$e[2]); }

			$sql = "delete from users where id={$this->id}";
			if (false === $PDO->exec($sql)) { $e = $PDO->errorInfo(); $PDO->rollBack(); throw new Exception($sql.$e[2]); }

			$PDO->commit();
		}

		private function update($fields)
		{
			global $PDO;

			$sql = "update users set $fields where id={$this->id}";

			if (false === $PDO->exec($sql)) { $e = $PDO->errorInfo(); throw new Exception($sql.$e[2]); }
		}

		private function insert($fields)
		{
			global $PDO;

			$sql = "insert users set $fields";


			if (false === $PDO->exec($sql)) { $e = $PDO->errorInfo(); throw new Exception($sql.$e[2]); }
			$this->id = $PDO->lastInsertID();

			# Save the initial password if we've added one
			if ($this->getPassword()) { $this->savePassword(); }
		}


		private function updateRoles()
		{
			global $PDO;

			$roles = $this->getRoles();

			$sql = "delete from user_roles where user_id={$this->id}";
			if (false === $PDO->exec($sql)) { $e = $PDO->errorInfo(); throw new Exception($sql.$e[2]); }

			$statement = $PDO->prepare("insert user_roles set user_id={$this->id},role_id=?");
			foreach($roles as $role_id=>$role)
			{
				if (false === $statement->execute(array("$role_id"))) { $e = $PDO->errorInfo(); throw new Exception($sql.$e[2]); }
			}
		}

		protected function saveLocalPassword()
		{
			global $PDO;

			$sql = "update users set password=md5('{$this->password}') where id={$this->id}";
			if (false === $PDO->exec($sql)) { $e = $PDO->errorInfo(); throw new Exception($sql.$e[2]); }
		}

		protected function authenticateDatabase($password)
		{
			global $PDO;

			$sql = "select id from users where username='{$this->username}' and password=md5('$password')";
			$result = $PDO->query($sql);
			if ($user = $result->fetch()) { return true; }
			else { return false; }
			$result->closeCursor();
		}
		/* Takes a string or an array of strings and checks if the user has that role */
		public function hasRole($roles)
		{
			if (is_array($roles))
			{
				foreach($roles as $role) { if (in_array($role,$this->getRoles())) { return true; } }
				return false;
			}
			else { return in_array($roles,$this->getRoles()); }
		}

		public function getId() { return $this->id; }
		public function getUsername() { return $this->username; }
		public function getPassword() { return $this->password; }
		public function getAuthenticationMethod() { return $this->authenticationMethod; }
		public function getFirstname() { return $this->firstname; }
		public function getLastname() { return $this->lastname; }

		public function getRoles()
		{
			global $PDO;

			if (!$this->roles)
			{
				$this->roles = array();
				$sql = "select role_id,role from user_roles left join roles on role_id=id where user_id={$this->id}";
				if ($result = $PDO->query($sql))
				{
					foreach($result as $row) { $this->roles[$row['role_id']] = $row['role']; }
					$result->closeCursor();
				}
			}
			return $this->roles;
		}

		public function setUsername($string) { $this->username = trim($string); }
		public function setPassword($string) { if ($string) { $this->password = $string; } }
		public function setAuthenticationMethod($string) { $this->authenticationMethod = $string; }
		public function setFirstname($string) { $this->firstname = trim($string); }
		public function setLastname($string) { $this->lastname = trim($string); }
		/* Takes an array of role names.  Needs to look up the role_id and add them to the user */
		public function setRoles($array)
		{
			$this->roles = array();
			foreach($array as $id)
			{
				$role = new Role($id);
				$this->roles[$role->getId()] = $role->getRole();
			}
		}
	}
?>