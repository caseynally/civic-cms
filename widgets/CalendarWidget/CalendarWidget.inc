<?php
/**
 * @copyright Copyright (C) 2007 City of Bloomington, Indiana. All rights reserved.
 * @license http://www.gnu.org/licenses/agpl.txt GNU/AGPL, see LICENSE.txt
 * @author Cliff Ingham <inghamn@bloomington.in.gov>
 */
class CalendarWidget extends Widget
{
	public function __construct()
	{
		$this->className = 'CalendarWidget';
		$this->displayName = 'Calendar';
		$this->includeFile = 'sidebar.inc';
		$this->description = 'Shows a small calendar with event dates highlighted';
	}

	public function render($template)
	{
		echo $this->renderIncludeFile($this);
	}

	/**
	 * This widget does not use an extra data
	 */
	public function usesData() { return false; }
	/**
	 * @ignore
	 */
	public function setData($string) { }
	/**
	 * @ignore
	 */
	public function serializePost(array $post) { }
	/**
	 * @ignore
	 */
	public function getDataFieldsetInclude() { return null; }
}
