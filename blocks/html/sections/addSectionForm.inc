<?php
/**
 * @copyright Copyright (C) 2006,2007,2008 City of Bloomington, Indiana. All rights reserved.
 * @license http://www.gnu.org/licenses/agpl.txt GNU/AGPL, see LICENSE.txt
 * @author Cliff Ingham <inghamn@bloomington.in.gov>
 */
	function printSectionOptions($section,$depth)
	{
		$name = View::escape($section->getName());
		$depthIndicator = str_repeat("-",$depth);
		echo "<li><label><input name=\"section[parents][{$section->getId()}]\" type=\"checkbox\" value=\"{$section->getId()}\" />$name</label></li>";
		if ($section->hasChildren())
		{
			echo "<ul style=\"list-style-type:none\">";
			foreach($section->getChildren() as $child) { printSectionOptions($child,$depth+1); }
			echo "</ul>";
		}
	}
?>
<h1>New Section</h1>
<form method="post" action="<?php echo $_SERVER['SCRIPT_NAME']; ?>">
<fieldset><legend>Section Info</legend>
	<table>
	<tr><td><label for="section-name" class="required">Name</label></td>
		<td><input name="section[name]" id="section-name" size="60" /></td></tr>
	<tr><td><label for="section-nickname">Nickname</label></td>
		<td><input name="section[nickname]" id="nickname" size="60" /></td></tr>
	</table>
</fieldset>

<fieldset><legend>Subscription Highlight</legend>
<p>If you make this section a Highlighted Subscription, it will show up on the special
"Subscriptions" page.</p>
<div>
<label>Highlight this subscription?</label>
<label><input name="section[highlightSubscription]" type="radio" value="1" />Yes</label>
<label><input name="section[highlightSubscription]" type="radio" value="0" checked="checked" />No</label>
</div>
</fieldset>

<fieldset><legend class="required">Departments</legend>
	<p>Choose the departments that will be allowed to post content to this section.</p>
	<p>You must choose at least one.</p>
	<table>
	<?php
		$departments = new DepartmentList();
		$departments->find();
		foreach($departments as $department)
		{
			$name = View::escape($department->getName());
			$checked = $_SESSION['USER']->getDepartment_id()===$department->getId() ? 'checked="checked"' : '';
			echo "
			<tr><td><input type=\"checkbox\" name=\"section[departments][{$department->getId()}]\" id=\"section-departments-{$department->getId()}\" value=\"{$department->getId()}\" $checked /></td>
				<td><label for=\"section-departments-{$department->getId()}\">$name</label></td></tr>
			";
		}
	?>
	</table>
</fieldset>

<fieldset><legend>Submit</legend>
	<button type="submit" class="save">Save</button>
	<a class="cancel" href="<?php echo BASE_URL; ?>/sections">Cancel</a>
</fieldset>
</form>
