<?php
/**
 * @copyright Copyright (C) 2007 City of Bloomington, Indiana. All rights reserved.
 * @license http://www.gnu.org/licenses/agpl.txt GNU/AGPL, see LICENSE.txt
 * @author Cliff Ingham <inghamn@bloomington.in.gov>
 * @param Facet $this->facet
 */
?>
<h1><?php echo View::escape($this->facet->getName()); ?></h1>
<div><?php echo WikiMarkup::parse($this->facet->getDescription()); ?></div>
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
			$title = View::escape($document->getTitle());
			echo "
			<li><a href=\"{$document->getURL()}\">$title</a></li>
			";
		}
	?>
</ul>
</div>
