<?php
/**
 * @copyright Copyright (C) 2006 City of Bloomington, Indiana. All rights reserved.
 * @license http://www.gnu.org/copyleft/gpl.html GNU/GPL, see LICENSE.txt
 */
/*
	$this->section
*/
	if (isset($this->section)) { $trails = $this->section->getAncestors(); }
	elseif (isset($this->document))
	{
		$trails = array();
		foreach($this->document->getSections() as $section)
		{
			$trails = array_merge($trails,$section->getAncestors());
		}
	}


	if (isset($trails))
	{
		echo "<div id=\"breadcrumbs\">";
		foreach($trails as $trail)
		{
			echo "<ul>";
			foreach($trail as $section)
			{
				echo "<li><a href=\"".BASE_URL."/sections/viewSection.php?section_id={$section->getId()}\">$section</a></li>";
			}
			echo "</ul>";
		}
		echo "</div>";
	}
?>