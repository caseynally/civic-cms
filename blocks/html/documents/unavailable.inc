<?php
/**
 * @copyright Copyright (C) 2007 City of Bloomington, Indiana. All rights reserved.
 * @license http://www.gnu.org/licenses/agpl.txt GNU/AGPL, see LICENSE.txt
 * @author Cliff Ingham <inghamn@bloomington.in.gov>
 * @param Document $this->document
 */
?>
<h2>Unpublished</h2>
<p>The page you were trying to view is currently unavailable.
<?php
	$now = time();
	if (strtotime($this->document->getPublishDate()) > $now)
	{
		echo 'This document will become active '.$this->document->getPublishDate('m/d/Y').'.';
	}
	else
	{
		echo 'This document was retired on '.$this->document->getRetireDate('m/d/Y').'.';
	}
?>
</p>
