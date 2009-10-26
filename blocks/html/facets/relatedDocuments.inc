<?php
/**
 * @copyright Copyright (C) 2007-2008 City of Bloomington, Indiana. All rights reserved.
 * @license http://www.gnu.org/copyleft/gpl.html GNU/GPL, see LICENSE.txt
 * @author Cliff Ingham <inghamn@bloomington.in.gov>
 * @param Facet $this->facet
 */
#--------------------------------------------------------------------
# Create the markup for the list of documents
# Remember the anchors we create, we're going to delay the rendering
# of this list, so we can display a table of contents on top
#--------------------------------------------------------------------
$displayedDocuments = array();
$anchors = array();
$output = '';
foreach($this->facet->getRelatedFacets() as $facet)
{
	if ( ($facet->getId() != $this->facet->getId()) &&
		 ($this->facet->getFacetGroup()->isRelated($facet->getFacetGroup())) )
	{
		$list = new DocumentList(array('facet_ids'=>array($this->facet->getId(),$facet->getId()),'active'=>date('Y-m-d')));
		if (count($list))
		{
			$name = View::escape($facet->getName());
			$anchor = WikiMarkup::wikify($facet->getName());
			$anchors[$anchor] = $name;
			$output.= "
			<h2><a id=\"$anchor\">$name</a></h2>
			<ul>
			";
			foreach($list as $document)
			{
				$displayedDocuments[$document->getId()] = $document;

				$title = $document->getFeature_title() ? $document->getFeature_title() : $document->getTitle();
				$title = View::escape($title);
				$output.= "<li><a href=\"{$document->getURL()}\">$title</a></li>\n";
			}
			$output.= "
			</ul>
			<a href=\"#top\">[Top]</a>
			";
		}
	}
}


#--------------------------------------------------------------------
# Table of Contents
# Go through all the anchors we've recorded and display them in
# a drop down list
#--------------------------------------------------------------------
$description = WikiMarkup::parse($this->facet->getDescription());
echo "<div>$description</div>";
if (count($displayedDocuments))
{
	echo "
	<div class=\"table-of-contents\">
		<form method=\"get\" action=\"$_SERVER[SCRIPT_NAME]\">
		<fieldset>
			<input type=\"hidden\" name=\"facet_id\" value=\"{$this->facet->getId()}\" />
			<label for=\"table-of-contents-anchor\">Table of Contents:</label>
			<select name=\"anchor\" id=\"table-of-contents-anchor\" onchange=\"document.location.href='#'+this.options[this.selectedIndex].value;\">
	";
			foreach($anchors as $anchor=>$name)
			{
				echo "<option value=\"$anchor\">$name</option>\n";
			}
	echo "
			</select>
		</fieldset>
		</form>
	</div>
	$output
	";
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
<?php
	$documents = $this->facet->getDocuments();
	# Don't bother showing anything if all these documents have already been listed above
	if (count($documents)>count($displayedDocuments))
	{
		if (count($displayedDocuments))
		{
			echo "
			<button type=\"button\" class=\"more\" onclick=\"toggleSiblings(this);\">More</button>
			<div id=\"siblings\" style=\"display:none;\">
			";
		}
		else { echo '<div id="siblings">'; }

		echo '<ul>';
		foreach($documents as $document)
		{
			if (!in_array($document->getId(),array_keys($displayedDocuments)))
			{
				$title = View::escape($document->getTitle());
				echo "<li><a href=\"{$document->getURL()}\">$title</a></li>";
			}
		}
		echo '</ul></div>';
	}
?>