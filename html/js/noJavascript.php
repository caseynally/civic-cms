<?php
/**
 * @copyright Copyright (C) 2007 City of Bloomington, Indiana. All rights reserved.
 * @license http://www.gnu.org/licenses/agpl.txt GNU/AGPL, see LICENSE.txt
 * @author Cliff Ingham <inghamn@bloomington.in.gov>
 * This page should be displayed whenever the user does not have Javascript
 */
	$_SESSION['errorMessages'][] = new Exception('noJavascript');
	$template = new Template();
	echo $template->render();
?>