<?php
/**
 * @copyright Copyright (C) 2006,2007 City of Bloomington, Indiana. All rights reserved.
 * @license http://www.gnu.org/copyleft/gpl.html GNU/GPL, see LICENSE.txt
 * @author Cliff Ingham <inghamn@bloomington.in.gov>
 */
?>
<h1>Update Calendar</h1>
<form method="post" action="<?php echo $_SERVER['PHP_SELF']; ?>">
<fieldset><legend>Calendar Info</legend>
	<input name="calendar_id" type="hidden" value="<?php echo $this->calendar->getId(); ?>" />
	<table>
	<tr><td><label for="calendar-name">Name</label></td>
		<td><input name="calendar[name]" id="calendar-name" value="<?php echo $this->calendar->getName(); ?>" /></td></tr>
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
			echo "
			<tr><td><input name=\"calendar[departments][{$department->getId()}]\" id=\"calendar-departments-{$department->getId()}\" type=\"checkbox\" value=\"{$department->getId()}\" $checked /></td>
				<td><label for=\"calendar-departments-{$department->getId()}\">$department</label></td></tr>
			";
		}
	?>
	</table>
</fieldset>

<fieldset><legend>Submit</legend>
	<button type="submit" class="submit">Submit</button>
	<button type="button" class="cancel" onclick="document.location.href='<?php echo BASE_URL; ?>/calendars';">Cancel</button>
</fieldset>
</form>