<?php
/**
 * @copyright Copyright (C) 2007 City of Bloomington, Indiana. All rights reserved.
 * @license http://www.gnu.org/copyleft/gpl.html GNU/GPL, see LICENSE.txt
 * @author Cliff Ingham <inghamn@bloomington.in.gov>
 */
	class NavigationWidget extends Widget
	{
		protected $section;
		protected $document;
		protected $ancestors;

		public function __construct()
		{
			$this->className = 'NavigationWidget';
			$this->displayName = 'Navigation';
			$this->includeFile = 'sidebar.inc';
			$this->description = 'Lists the sub-sections for the current section';
		}

		public function render($template)
		{

			if (isset($template->document))
			{
				global $section;
				$this->section = $section;
				$this->document = $template->document;

				# Keep a running history of a user's section navigation
				if (!isset($_SESSION['sectionHistory'])) { $_SESSION['sectionHistory'] = array(); }
				$_SESSION['sectionHistory'][] = $this->section->getId();

				# Figure out which ancestral line we want to display in the navigation
				$ancestors = $this->section->getAncestors();
				if (count($_SESSION['sectionHistory']) > 1)
				{
					$previousSectionId = array_slice($_SESSION['sectionHistory'],-2,1);

					# Check all the vectors in the ancestor array.
					# If the last section in that vector matches the previousSectionId,
					# that's the vector we want to display for navigation
					foreach($ancestors as $vector)
					{
						$parent = end($vector);
						if ($parent->getId() == $previousSectionId)
						{
							# This is the vector we want to display;
							$this->ancestors = $vector;
						}
					}
				}

				# If we weren't able to find a vector, just use the first available
				if (!$this->ancestors) { $this->ancestors = $ancestors[0]; }

				$this->renderIncludeFile($this);
			}
		}
	}
?>