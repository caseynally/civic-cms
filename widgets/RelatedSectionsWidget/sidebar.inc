<?php
/**
 * @copyright Copyright (C) 2007 City of Bloomington, Indiana. All rights reserved.
 * @license http://www.gnu.org/licenses/agpl.txt GNU/AGPL, see LICENSE.txt
 * @author Cliff Ingham <inghamn@bloomington.in.gov>
 * @param SectionList $this->sectionList
 */
?>
<div class="widget">
	<h1>Related Sections</h1>
	<ul>
	<?php
		foreach($this->sectionList as $section)
		{
			echo "
			<li><a href=\"".BASE_URL."/sections/viewSection.php?section_id={$section->getId()}\">$section</a></li>
			";
		}
	?>
	</ul>
</div>
