<?php
/**
 * @copyright Copyright (C) 2006,2007 City of Bloomington, Indiana. All rights reserved.
 * @license http://www.gnu.org/licenses/agpl.txt GNU/AGPL, see LICENSE.txt
 * @author Cliff Ingham <inghamn@bloomington.in.gov>
 */
?>
<h1>Update Calendar</h1>
<form method="post" action="<?php echo $_SERVER['SCRIPT_NAME']; ?>">
<fieldset><legend>Calendar Info</legend>
	<input name="calendar_id" type="hidden" value="<?php echo $this->calendar->getId(); ?>" />
	<table>
	<tr><td><label for="calendar-name">Name</label></td>
		<td><input name="calendar[name]" id="calendar-name" size="60" value="<?php echo View::escape($this->calendar->getName()); ?>" /></td></tr>
	<tr><td colspan="2">
			<label for="calendar-description" class="required">Description</label>
			<textarea name="calendar[description]" id="calendar-description" rows="3" cols="60"><?php echo View::escape($this->calendar->getDescription()); ?></textarea>
	</td></tr>
	</table>
</fieldset>

<fieldset><legend>Departments</legend>
	<table>
	<?php
		$list = new DepartmentList();
		$list->find();
		foreach($list as $department)
		{
			$checked = $this->calendar->hasDepartment($department) ? 'checked="checked"' : '';
			$name = View::escape($department->getName());
			echo "
			<tr><td><input name=\"calendar[departments][{$department->getId()}]\" id=\"calendar-departments-{$department->getId()}\" type=\"checkbox\" value=\"{$department->getId()}\" $checked /></td>
				<td><label for=\"calendar-departments-{$department->getId()}\">$name</label></td></tr>
			";
		}
	?>
	</table>
</fieldset>

<fieldset><legend>Submit</legend>
	<button type="submit" class="submit">Submit</button>
	<a class="cancel" href="<?php echo BASE_URL; ?>/calendars">Cancel</a>
</fieldset>
</form>
