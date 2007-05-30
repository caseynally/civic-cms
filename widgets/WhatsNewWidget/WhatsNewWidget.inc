<?php
/**
 * @copyright Copyright (C) 2006 City of Bloomington, Indiana. All rights reserved.
 * @license http://www.gnu.org/copyleft/gpl.html GNU/GPL, see LICENSE.txt
 * @author Cliff Ingham <inghamn@bloomington.in.gov>
 */
	class WhatsNewWidget extends Widget
	{
		protected $sectionIds = array();
		protected $documents = array();

		public function __construct()
		{
			$this->className = 'WhatsNewWidget';
			$this->displayName = 'Whats New';
			$this->includeFile = 'sidebar.inc';
			$this->description = 'Lists all documents in the current section or any sub-section published in the last 4 months';
		}

		public function render($template)
		{
			global $PDO;

			if (isset($template->document))
			{

				foreach($template->document->getSections() as $section)
				{
					$this->sectionIds[] = $section->getId();
					if (count($section->getDescendants()))
					{
						$this->sectionIds = array_merge(array_keys($section->getDescendants()),$this->sectionIds);
					}
				}

				$documentIds = array();
				$sections= implode(',',$this->sectionIds);
				$sql = "select d.id from document_sections s left join documents d on s.document_id=d.id
						where s.section_id in ($sections)
						and d.publishDate > date_sub(CURRENT_DATE,interval 4 month)";
				foreach($PDO->query($sql) as $row) { $documentIds[] = $row['id']; }
				foreach($documentIds as $id) { $this->documents[$id] = new Document($id); }

				$this->renderIncludeFile($this);
			}
		}
	}
?>