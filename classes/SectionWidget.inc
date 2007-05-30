<?php
/**
 * @copyright Copyright (C) 2007 City of Bloomington, Indiana. All rights reserved.
 * @license http://www.gnu.org/copyleft/gpl.html GNU/GPL, see LICENSE.txt
 * @author Cliff Ingham <inghamn@bloomington.in.gov>
 */
	class SectionWidget extends ActiveRecord
	{
		private $id;
		private $section_id;
		private $widget_id;
		private $panel_id;
		private $layout_order;


		private $section;
		private $widget;
		private $panel;



		/**
		 * This will load all fields in the table as properties of this class.
		 * You may want to replace this with, or add your own extra, custom loading
		 */
		public function __construct($id=null)
		{
			global $PDO;

			if ($id)
			{
				$sql = 'select * from section_widgets where id=?';
				try
				{
					$query = $PDO->prepare($sql);
					$query->execute(array($id));
				}
				catch (Exception $e) { throw $e; }

				$result = $query->fetchAll();
				foreach($result[0] as $field=>$value) { if ($value) $this->$field = $value; }
			}
			else
			{
				# This is where the code goes to generate a new, empty instance.
				# Set any default values for properties that need it here
			}
		}


		/**
		 * This generates generic SQL that should work right away.
		 * You can replace this $fields code with your own custom SQL
		 * for each property of this class,
		 */
		public function save()
		{
			# Check for required fields here.  Throw an exception if anything is missing.
			if (!$this->section_id || !$this->widget_id || !$this->panel_id) { throw new Exception('missingRequiredFields'); }

			$fields = array();
			$fields['section_id'] = $this->section_id ? $this->section_id : null;
			$fields['widget_id'] = $this->widget_id ? $this->widget_id : null;
			$fields['panel_id'] = $this->panel_id ? $this->panel_id : null;
			$fields['layout_order'] = $this->layout_order ? $this->layout_order : null;

			# Split the fields up into a preparedFields array and a values array.
			# PDO->execute cannot take an associative array for values, so we have
			# to strip out the keys from $fields
			$preparedFields = array();
			foreach($fields as $key=>$value)
			{
				$preparedFields[] = "$key=?";
				$values[] = $value;
			}
			$preparedFields = implode(",",$preparedFields);


			if ($this->id) { $this->update($values,$preparedFields); }
			else { $this->insert($values,$preparedFields); }
		}

		private function update($values,$preparedFields)
		{
			global $PDO;

			$sql = "update section_widgets set $preparedFields where id={$this->id}";
			if (false === $query = $PDO->prepare($sql)) { $e = $PDO->errorInfo(); throw new Exception($sql.$e[2]); }
			if (false === $query->execute($values)) { $e = $PDO->errorInfo(); throw new Exception($sql.$e[2]); }
		}

		private function insert($values,$preparedFields)
		{
			global $PDO;

			$sql = "insert section_widgets set $preparedFields";
			if (false === $query = $PDO->prepare($sql)) { $e = $PDO->errorInfo(); throw new Exception($sql.$e[2]); }
			if (false === $query->execute($values)) { $e = $PDO->errorInfo(); throw new Exception($sql.$e[2]); }
			$this->id = $PDO->lastInsertID();
		}

		public function delete()
		{
			global $PDO;

			$sql = 'delete from section_widgets where id=?';
			if (false === $query = $PDO->prepare($sql)) { $e = $PDO->errorInfo(); throw new Exception($sql.$e[2]); }
			if (false === $query->execute(array($this->id))) { $e = $PDO->errorInfo(); throw new Exception($sql.$e[2]); }
		}

		/**
		 * Aliases for WidgetInstallation functions
		 */
		public function render($template) { $this->getWidget()->render($template); }

		/**
		 * Generic Getters
		 */
		public function getId() { return $this->id; }
		public function getSection_id() { return $this->section_id; }
		public function getWidget_id() { return $this->widget_id; }
		public function getPanel_id() { return $this->panel_id; }
		public function getLayout_order() { return $this->layout_order; }
		public function getName() { return $this->getWidget()->getName(); }

		public function getSection()
		{
			if ($this->section_id)
			{
				if (!$this->section) { $this->section = new Section($this->section_id); }
				return $this->section;
			}
			else return null;
		}

		public function getWidget()
		{
			if ($this->widget_id)
			{
				if (!$this->widget) { $this->widget = new WidgetInstallation($this->widget_id); }
				return $this->widget;
			}
			else return null;
		}

		public function getPanel()
		{
			if ($this->panel_id)
			{
				if (!$this->panel) { $this->panel = new Panel($this->panel_id); }
				return $this->panel;
			}
			else return null;
		}

		/**
		 * Generic Setters
		 */
		public function setSection_id($int) { $this->section = new Section($int); $this->section_id = $int; }
		public function setWidget_id($int) { $this->widget = new WidgetInstallation($int); $this->widget_id = $int; }
		public function setPanel_id($int) { $this->panel = new Panel($int); $this->panel_id = $int; }
		public function setLayout_order($int) { $this->layout_order = ereg_replace("[^0-9]","",$int); }

		public function setSection($section) { $this->section_id = $section->getId(); $this->section = $section; }
		public function setWidget($widget) { $this->widget_id = $widget->getId(); $this->widget = $widget; }
		public function setPanel($panel) { $this->panel_id = $panel->getId(); $this->panel = $panel; }
	}
?>