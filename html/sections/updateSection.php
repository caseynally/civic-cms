<?php
/*
	$_GET variables:	section_id
*/
	verifyUser('Webmaster');

	if (isset($_GET['section_id'])) { $section = new Section($_GET['section_id']); }
	if (isset($_POST['section']))
	{
		$section = new Section($_POST['id']);

		$_POST['section']['facets'] = isset($_POST['section']['facets']) ? $_POST['section']['facets'] : array();
		foreach($_POST['section'] as $field=>$value)
		{
			$set = "set".ucfirst($field);
			$section->$set($value);
		}
		try
		{
			$section->save();
			Header("Location: home.php");
			exit();
		}
		catch (Exception $e) { $_SESSION['errorMessages'][] = $e; }
	}

	$template = new Template();
	$template->blocks[] = new Block("sections/updateSectionForm.inc",array('section'=>$section));
	$template->render();
?>