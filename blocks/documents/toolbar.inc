<?php
/**
 * @copyright Copyright (C) 2006 City of Bloomington, Indiana. All rights reserved.
 * @license http://www.gnu.org/copyleft/gpl.html GNU/GPL, see LICENSE.txt
 */
/*
	$this->document
	( $this->section )
*/
?>
<div class="contextualMenu">
	<ul><li><a href="<?php echo BASE_URL; ?>/documents/updateDocument.php?document_id=<?php echo $this->document->getId(); ?>">Edit Document</a></li>
		<?php
			if (isset($this->section))
			{
				echo "<li><a href=\"".BASE_URL."/documents/addDocument.php?section_id={$this->section->getId()}\">Add Document</a></li>";
			}

			if ($_SESSION['USER']->hasWatch($this->document)) { echo "<li><a href=\"".BASE_URL."/documents/removeWatch.php?document_id={$this->document->getId()}\">Remove Watch</a></li>"; }
			else { echo "<li><a href=\"".BASE_URL."/documents/addWatch.php?document_id={$this->document->getId()}\">Add Watch</a></li>"; }
		?>
	</ul>
</div>