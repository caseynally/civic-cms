<?php
/**
 * @copyright Copyright (C) 2006-2008 City of Bloomington, Indiana. All rights reserved.
 * @license http://www.gnu.org/licenses/agpl.txt GNU/AGPL, see LICENSE.txt
 * @author Cliff Ingham <inghamn@bloomington.in.gov>
 */
?>
<a href="https://bloomington.in.gov/alpha" class="alphaAnnouncement">
	<span class="alphaAnnouncement-container">
		New: Bloomington.in.gov/alpha. Your feedback can help make our next website better!
	</span>
</a>
<div id="banner">
	<div id="logo"><a href="<?php echo BASE_URL; ?>/">City of Bloomington, IN</a></div>
	<div id="skipNavigation"><a href="#mainContent" title="Skip Navigation">Skip Navigation</a></div>
	<div class="widgets">
		<?php
			$panel = new Panel('banner');
			$widgets = isset($this->document) ? $panel->getWidgets($this->document) : $panel->getWidgets();

			foreach($widgets as $widget) { $widget->render($this); }
		?>
	</div>
	<div id="mainLinks">
		<ul><li class="first"><a href="<?php echo BASE_URL; ?>/documentTypes/documents.php?documentType_id=4">Services</a></li>
			<li><a href="<?php echo BASE_URL; ?>/documentTypes/documents.php?documentType_id=5">News</a></li>
			<li><a href="<?php echo BASE_URL; ?>/calendars">Calendars</a></li>
			<li><a href="<?php echo BASE_URL; ?>/locations">Locations</a></li>
			<li><a href="<?php echo BASE_URL; ?>/mybloomington">myBloomington</a></li>
			<li><a href="<?php echo BASE_URL; ?>/search/sitemap.php">Sitemap</a></li>
		</ul>
	</div>
	<div id="secondaryLinks">
	<ul><li class="first"><a href="<?php echo BASE_URL; ?>/subscribe">Subscribe</a></li>
		<li><a href="<?php echo BASE_URL; ?>/contact">Contact Us</a></li>
		<li><?php include APPLICATION_HOME.'/blocks/html/search/searchForm.inc'; ?></li>
	</ul>
	</div>
</div>
