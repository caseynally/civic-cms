<?php
/**
 * @copyright Copyright (C) 2006,2007 City of Bloomington, Indiana. All rights reserved.
 * @license http://www.gnu.org/copyleft/gpl.html GNU/GPL, see LICENSE.txt
 * @author Cliff Ingham <inghamn@bloomington.in.gov>
 * @param LocationList $this->locationList
 */
?>
<div class="interfaceBox">
	<div class="titleBar">
		<button type="button" class="addSmall" onclick="document.location.href='<?php echo BASE_URL; ?>/locations/addLocation.php';">Add</button>
		Locations
	</div>
	<ul><?php
			$points = array();
			$info = array();
			foreach($this->locationList as $location)
			{
				$points[] = "new GLatLng({$location->getLatitude()},{$location->getLongitude()})";
				$info[] = "\"{$this->escape($location->getName())}\"";

				$i = count($points) - 1;
				echo "
				<li><button type=\"button\" class=\"editSmall\" onclick=\"document.location.href='".BASE_URL."/locations/updateLocation.php?id={$location->getId()}';\">Edit</button>
					<a href=\"#map\" onclick=\"popup($i);\">
					$location</a>
				</li>
				";
			}
		?>
	</ul>
</div>
<h2><a name="map">Map</a></h2>
<div id="map" style="width:500px; height:500px; border:1px solid black;">
</div>
<script src="http://maps.google.com/maps?file=api&amp;v=2.77&amp;key=ABQIAAAACqoQOZ2EAqg13jBR94AfexSOTeGX9w6TRh8-t3vLxMlcuGJjjBRSGREuz9NdVZhhWOn4Un1qDAxx2Q" type="text/javascript"></script>
<script type="text/javascript">
	<?php
		foreach($this->locationList as $location)
		{
		}
		$points = implode(',',$points);
		$info = implode(',',$info);

		echo "var points = [$points];\n";
		echo "var info = [$info];\n";
	?>
	if (GBrowserIsCompatible())
	{
		// Create map and add controls
		var map = new GMap2(document.getElementById("map"));
		map.addControl(new GSmallMapControl());
		map.addControl(new GMapTypeControl());
		map.setCenter(new GLatLng(39.167119,-86.533800), 12);

		for(var i=0; i<points.length; i++) { map.addOverlay(createMarker(points[i],info[i])); }
	}

    //Create a marker with your own icon or with default icon (where icon = null)
	function createMarker(point, info, icon)
	{
		if (icon == null) { var marker = new GMarker(point); }
		else { var marker = new GMarker(point, icon); }
		GEvent.addListener(marker, "click", function() { marker.openInfoWindowHtml(info); });
		return marker;
	}

	function popup(point)
	{
		if (map)
		{
			map.openInfoWindowHtml(points[point],info[point]);
			return false;
		}
		else { return true; }
	}
</script>