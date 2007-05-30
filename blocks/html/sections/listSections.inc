<?php
/**
 * @copyright Copyright (C) 2006,2007 City of Bloomington, Indiana. All rights reserved.
 * @license http://www.gnu.org/copyleft/gpl.html GNU/GPL, see LICENSE.txt
 * @author Cliff Ingham <inghamn@bloomington.in.gov>
 * @param Section $this->section
 */
	function listEditableSections($section)
	{
		foreach($section->getChildren() as $placement=>$section)
		{
			$name = View::escape($section->getName());
			if (userHasRole('Webmaster'))
			{
				$buttons = "
				<button type=\"button\" class=\"editSmall\" onclick=\"document.location.href='".BASE_URL."/sections/updateSection.php?section_id={$section->getId()}';\">Edit</button>
				<button type=\"button\" class=\"deleteSmall\" onclick=\"FRAMEWORK.deleteConfirmation('".BASE_URL."/sections/deleteSection.php?section_id={$section->getId()}');\">Delete</button>
				<button type=\"button\" class=\"widgets\" onclick=\"document.location.href='".BASE_URL."/sections/updateWidgets.php?section_id={$section->getId()}';\">Widgets</button>
				";

			}
			echo "
			<li><a href=\"".BASE_URL."/documents/viewDocument.php?document_id={$section->getDocument_id()}\">
				$name</a>
				$buttons
			";

			if ($section->hasChildren())
			{
				echo "<ul>";
				listEditableSections($section);
				echo "</ul>";
			}

			echo "</li>";
		}
	}
?>
<div class="interfaceBox">
<?php
	if (userHasRole('Webmaster'))
	{
		echo "
		<div class=\"contextualMenu\">
			<span class=\"title\">Sections</span>
			<ul><li><a href=\"".BASE_URL."/sections/addSection.php\">Add</a></li>
				<li><a href=\"".BASE_URL."/sections/rearrangeSections.php\">Rearrange</a></li>
			</ul>
		</div>
		";
	}
	else { echo "<div class=\"titleBar\">Sections</div>"; }
?>
	<ul class="expandable">
		<?php listEditableSections($this->section); ?>
	</ul>
</div>
<script type="text/javascript" src="<?php echo BASE_URL; ?>/tree.js"></script>