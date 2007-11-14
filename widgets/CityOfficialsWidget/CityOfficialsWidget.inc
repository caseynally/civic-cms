<?php
/**
 * @copyright Copyright (C) 2007 City of Bloomington, Indiana. All rights reserved.
 * @license http://www.gnu.org/copyleft/gpl.html GNU/GPL, see LICENSE.txt
 * @author Cliff Ingham <inghamn@bloomington.in.gov>
 */
class CityOfficialsWidget extends Widget
{
	protected $languages;

	public function __construct()
	{
		$this->className = 'CityOfficialsWidget';
		$this->displayName = 'City Officials';
		$this->includeFile = 'sidebar.inc';
		$this->description = 'Displays the list City Officials';
	}

	public function render($template)
	{
		if (isset($template->document))
		{
			$this->renderIncludeFile($this);
		}
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