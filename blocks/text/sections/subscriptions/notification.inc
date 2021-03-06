<?php
/**
 * @copyright Copyright (C) 2008 City of Bloomington, Indiana. All rights reserved.
 * @license http://www.gnu.org/licenses/agpl.txt GNU/AGPL, see LICENSE.txt
 * @author Cliff Ingham <inghamn@bloomington.in.gov>
 * @param string $this->message
 * @param Section $this->section
 * @param array $this->documents
 */
echo "{$this->message}\n\n";
if (count($this->documents))
{
	foreach($this->documents as $document)
	{
		echo "{$document->getTitle()}\n";
		echo "{$document->getURL()}\n\n";
	}
}
else
{
	echo "{$this->section->getName()}\n";
	echo "{$this->section->getURL()}\n\n";
}