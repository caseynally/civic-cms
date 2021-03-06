<?php
/**
 * @copyright Copyright (C) 2008 City of Bloomington, Indiana. All rights reserved.
 * @license http://www.gnu.org/licenses/agpl.txt GNU/AGPL, see LICENSE.txt
 * @author Cliff Ingham <inghamn@bloomington.in.gov>
 * @param AlertType $this->alertType
 */
$type = $this->alertType->getName();
$list = new AlertList(array('alertType_id'=>$this->alertType->getId()));
if (count($list))
{
	if ($type=='Weather')
	{
		echo "
		<div class=\"weatheralert widget\">
		<h1>Severe Weather Alerts</h1>
		<ul>
		";
		foreach($list as $alert)
		{
			$title = View::escape($alert->getTitle());
			$text = $alert->getURL() ? "<a href=\"{$alert->getURL()}\">$title</a>" : $title;
			echo "<li>$text</li>";
		}
		echo "
		</ul>
		</div>
		";
	}
	else
	{
		echo '<div class="widget">';
		foreach($list as $alert)
		{
			$title = View::escape($alert->getTitle());
			$title = $alert->getURL() ? "<a href=\"{$alert->getURL()}\">$title</a>" : $title;
			$text = View::escape($alert->getText());
			echo "
			<div class=\"customalert\">
				<h1>$title</h1>
				<p>$text</p>
			</div>
			";
		}
		echo '</div>';
	}
}
