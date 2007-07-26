<?php
/**
 * @copyright Copyright (C) 2007 City of Bloomington, Indiana. All rights reserved.
 * @license http://www.gnu.org/copyleft/gpl.html GNU/GPL, see LICENSE.txt
 * @author Cliff Ingham <inghamn@bloomington.in.gov>
 * @param Facet $this->facet
 */
	$name = View::escape($this->facet->getName());
	$description = View::escape($this->facet->getDescription());
	echo "
	<h2>$name</h2>
	<p>$description</p>
	";

	$displayedDocuments = array();
	foreach($this->facet->getRelatedGroups() as $group)
	{
		foreach($group->getFacets() as $facet)
		{
			if ($facet->getId() != $this->facet->getId())
			{
				$list = new DocumentList(array('facet_id'=>array($this->facet->getId(),$facet->getId())));
				if (count($list))
				{
					$name = View::escape($facet->getName());
					echo "
					<div class=\"interfaceBox\">
						<div class=\"titleBar\">$name</div>
						<ul>
					";
						foreach($list as $document)
						{
							$displayedDocuments[$document->getId()] = $document;

							$title = View::escape($document->getTitle());
							echo "<li><a href=\"{$document->getURL()}\">$title</a></li>\n";
						}
					echo "
						</ul>
					</div>
					";
				}
			}
		}
	}
?>
<script type="text/javascript">
	function toggleSiblings(button)
	{
		var siblings = document.getElementById('siblings');
		if (siblings.style.display === 'none')
		{
			// Display the siblings
			siblings.style.display = '';
			button.className = 'less';
			button.firstChild.nodeValue = 'Less';
		}
		else
		{
			// Hide the siblings
			siblings.style.display = 'none';
			button.className = 'more';
			button.firstChild.nodeValue = 'More';
		}
	}
</script>
<button type="button" class="more" onclick="toggleSiblings(this);">More</button>
<div id="siblings" style="display:none;">
<ul><?php
		foreach($this->facet->getDocuments() as $document)
		{
			if (!in_array($document->getId(),array_keys($displayedDocuments)))
			{
				$title = View::escape($document->getTitle());
				echo "
				<li><a href=\"{$document->getURL()}\">$title</a></li>
				";
			}
		}
	?>
</ul>
</div>