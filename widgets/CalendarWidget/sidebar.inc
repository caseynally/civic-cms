<?php
/**
 * @copyright Copyright (C) 2007 City of Bloomington, Indiana. All rights reserved.
 * @license http://www.gnu.org/copyleft/gpl.html GNU/GPL, see LICENSE.txt
 * @author Cliff Ingham <inghamn@bloomington.in.gov>
 */
	$calendar = new Calendar();
	$date = getdate();

	$timestamp = mktime(0,0,0,$date['mon'],1,$date['year']);
	$endRange = strtotime('+1 month',$timestamp);
	$recurrences = $calendar->getEventRecurrenceArray($timestamp,$endRange);

	$calendarDate = getdate($timestamp);
	$year = $calendarDate['year'];
	$month = str_pad($calendarDate['mon'],2,'0',STR_PAD_LEFT);
	$lastDayOfMonth = date('t',$timestamp);
?>
<table class="calendar">
<tr><th colspan="7"><?php echo $calendarDate['month']; ?></th></tr>
<tr><th>S</th><th>M</th><th>T</th><th>W</th><th>R</th><th>F</th><th>S</th></tr>
<?php
	$firstWeekDay = $calendarDate['wday'];
	$currentWeekDay = $firstWeekDay;
	$firstweek = true;
	$currentDay = 1;

	# Loop through all the days of the month
	while($currentDay <= $lastDayOfMonth)
	{
		# Draw blank days for the first week
		if ($firstweek)
		{
			echo "<tr>";
			for($i=1; $i<=$firstWeekDay; $i++) { echo "<td></td>"; }
			$firstweek = false;
		}

		# Start a new row each sunday
		if ($currentWeekDay == 0) { echo "<tr>"; }

		# Markup for a single day in the calendar
		$url = new URL(BASE_URL.'/calendars');
		$url->parameters = array('year'=>$year,'mon'=>$month,'mday'=>$currentDay);
		if ($calendar->getId()) { $url->parameters['calendar_id'] = $calendar->getId(); }
		$url->parameters['view'] = 'day';

		$day = str_pad($currentDay,2,'0',STR_PAD_LEFT);
		if (isset($recurrences[$year][$month][$day])) { echo "<td class=\"event\"><a href=\"{$url->getURL()}\">$currentDay</a>"; }
		else { echo "<td>$currentDay"; }
		echo "</td>";


		# Close off each row on Saturday
		if ($currentWeekDay == 6) { echo "</tr>"; }



		$currentWeekDay++;
		$currentWeekDay = $currentWeekDay % 7;
		$currentDay++;
	}

	# Finish out the table with blank days
	for($i=$currentWeekDay; $i % 7 != 0; $i++) { echo "<td></td>"; }

?>
</tr>
</table>