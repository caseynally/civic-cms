<?php
/**
 * @copyright Copyright (C) 2007-2008 City of Bloomington, Indiana. All rights reserved.
 * @license http://www.gnu.org/licenses/agpl.txt GNU/AGPL, see LICENSE.txt
 * @author Cliff Ingham <inghamn@bloomington.in.gov>
 * @param GET documentType_id
 * @param GET facetGroup_id
 *
 * Displays the documents of a given DocumentType, organized by Facet
 */
if (isset($_GET['documentType_id']) && $_GET['documentType_id'])
{
	try { $type = new DocumentType($_GET['documentType_id']); }
	catch (Exception $e)
	{
		$_SESSION['errorMessages'][] = $e;
		Header('Location: home.php');
		exit();
	}

	$template = (isset($_GET['format'])) ? new Template('default',$_GET['format']) : new Template();

	$block = new Block('documentTypes/documents.inc',array('documentType'=>$type));
	if (isset($_GET['facetGroup_id']))
	{
		if (is_numeric($_GET['facetGroup_id']) && $_GET['facetGroup_id']>0)
		{
			try {
				$block->facetGroup = new FacetGroup($_GET['facetGroup_id']);
			}
			catch (Exception $e) {
				// Just ignore the unknown facetGroup
			}
		}
	}
	else {
		# Load the default Facet Group
		if ($type->getDefaultFacetGroup_id()) { $block->facetGroup = $type->getDefaultFacetGroup(); }
	}


	if ($template->outputFormat=='html')
	{
		$template->blocks[] = new Block('documentTypes/breadcrumbs.inc',array('documentType'=>$type));
	}

	$template->blocks[] = $block;
	echo $template->render();
}
else
{
	Header('Location: home.php');
}
