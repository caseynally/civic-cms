<?php
/**
 * @copyright Copyright (C) 2007 City of Bloomington, Indiana. All rights reserved.
 * @license http://www.gnu.org/copyleft/gpl.html GNU/GPL, see LICENSE.txt
 * @author Cliff Ingham <inghamn@bloomington.in.gov>
 * @param GET section_id
 * @param GET widget_id
 */
	verifyUser(array('Administrator','Webmaster'));

	if (isset($_GET['section_id']) && isset($_GET['widget_id']))
	{
		$section = new Section($_GET['section_id']);
		$widget = new WidgetInstallation($_GET['widget_id']);
	}

	if (isset($_POST['sectionWidget']))
	{
		$sectionWidget = new SectionWidget();
		foreach($_POST['sectionWidget'] as $field=>$value)
		{
			$set = 'set'.ucfirst($field);
			$sectionWidget->$set($value);
		}
		$sectionWidget->setData($sectionWidget->getWidget()->getWidget()->serializePost($_POST));

		try
		{
			$sectionWidget->save();
			Header('Location: updateWidgets.php?section_id='.$sectionWidget->getSection_id());
			exit();
		}
		catch (Exception $e)
		{
			$_SESSION['errorMessages'][] = $e;
			$section = $sectionWidget->getSection();
			$widget = $sectionWidget->getWidget();
		}
	}

	$template = new Template();
	$template->blocks[] = new Block('sections/addWidgetForm.inc',array('section'=>$section,'widget'=>$widget));
	$template->render();
?>