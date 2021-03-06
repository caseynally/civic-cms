<?php
/**
 * @copyright Copyright (C) 2007,2008 City of Bloomington, Indiana. All rights reserved.
 * @license http://www.gnu.org/licenses/agpl.txt GNU/AGPL, see LICENSE.txt
 * @author Cliff Ingham <inghamn@bloomington.in.gov>
 * Lists all the locationGroups.  This script was added so we'd have a controller
 * to provide this list as a web service.  For webservices, we want a separate list
 * for the LocationGroups, and a seperate list for the Locations
 */
$template = isset($_GET['format']) ? new Template('default',$_GET['format']) : new Template();

$groupList = new LocationGroupList();
$groupList->find();
$template->blocks[] = new Block('locations/locationGroupList.inc',array('locationGroupList'=>$groupList));

echo $template->render();
