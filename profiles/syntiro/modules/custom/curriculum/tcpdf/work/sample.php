<?php

require_once('../config/lang/eng.php');
require_once('../tcpdf.php');


// Extend the TCPDF class to create custom Header and Footer
class MYPDF extends TCPDF {

    //Page header
    public function Header() {
				$this->Cell(0, 5, 'Group Trip Itinerary for...', 0, 1, 'C', 0, '', 0, false, 'M', 'M');
        // Logo
        $image_file = 'http://tripcaddie/sites/all/modules/custom/tc_itinerary_printpdf/tcpdf/images/tripcaddie_logo.png';
        $this->Image($image_file, 0, 10, '35', '', 'PNG', 'http://www.tripcaddie.betabasket.net/', 'C', false, 300, 'C', false, false, 0, false, false, false);
        // Set font
        $this->SetFont('dejavuserifbi', 'B', 12);
        // Title
        $this->Cell(0, 65, '< GROUP NAME HERE >', 0, 1, 'C', 0, '', 0, false, 'M', 'M');
				$style2 = array('width' => 0.5, 'cap' => 'butt', 'join' => 'miter', 'dash' => 0, 'color' => array(0, 0, 255));
				
				$this->Line(10, 46, 200, 46, $style2);
				
    }
		
    // Page footer
    public function Footer() {
        // Position at 15 mm from bottom
        $this->SetY(-20);
        // Set font
        $this->SetFont('dejavuserifbi', 'I', 10);
				
				$style2 = array('width' => 0.5, 'cap' => 'butt', 'join' => 'miter', 'dash' => 0, 'color' => array(0, 0, 255));
				$this->Line(10, 265, 200, 265, $style2); // Horizantal Line
				$this->Line(40, 265, 40, 290, $style2); // Vertical Line
        // Page number
        $this->Cell(55, 0, 'Page '.$this->getAliasNumPage(), 0, false, '', 0, '', 0, false, 'T', 'M');
				$image_file = 'http://tripcaddie/sites/all/modules/custom/tc_itinerary_printpdf/tcpdf/images/tripcaddie_footer.jpg';				
				$this->Image($image_file, 44, 267, '25', '20', 'JPG', 'http://www.tripcaddie.betabasket.net/', 'N', false, 300, '', false, false, 0, false, false, false);												
				/*
				$this->SetXY(75,-28);
				$this->Cell(0, 0, 'TripCaddie.com - Where Buddies PLAN Golf Trips!', 0, 1, '', 0, '', 0, false, 'M', 'M');
				$this->SetXY(75,-20);
				$this->Cell(0, 0, 'Copyright TripCaddie, LLC &copy;. All rights reserved.', 0, 1, '', 0, '', 0, false, 'M', 'M');/**/
    }
}

// create new PDF document
$pdf = new MYPDF(PDF_PAGE_ORIENTATION, PDF_UNIT, PDF_PAGE_FORMAT, true, 'UTF-8', false);

// set document information
$pdf->SetCreator(PDF_CREATOR);
$pdf->SetAuthor('Nicola Asuni');
$pdf->SetTitle('TCPDF Example 003');
$pdf->SetSubject('TCPDF Tutorial');
$pdf->SetKeywords('TCPDF, PDF, example, test, guide');

// set default header data
$pdf->SetHeaderData(PDF_HEADER_LOGO, PDF_HEADER_LOGO_WIDTH, PDF_HEADER_TITLE, PDF_HEADER_STRING);

// set header and footer fonts
$pdf->setHeaderFont(Array(PDF_FONT_NAME_MAIN, '', PDF_FONT_SIZE_MAIN));
$pdf->setFooterFont(Array(PDF_FONT_NAME_DATA, '', PDF_FONT_SIZE_DATA));

// set default monospaced font
$pdf->SetDefaultMonospacedFont(PDF_FONT_MONOSPACED);

//set margins
$pdf->SetMargins(PDF_MARGIN_LEFT, PDF_MARGIN_TOP, PDF_MARGIN_RIGHT);
$pdf->SetHeaderMargin(PDF_MARGIN_HEADER);
$pdf->SetFooterMargin(PDF_MARGIN_FOOTER);

//set auto page breaks
$pdf->SetAutoPageBreak(TRUE, PDF_MARGIN_BOTTOM);

//set image scale factor
$pdf->setImageScale(PDF_IMAGE_SCALE_RATIO);

//set some language-dependent strings
$pdf->setLanguageArray($l);

// ---------------------------------------------------------

// set font
$pdf->SetFont('times', 'BI', 12);

// add a page
$pdf->AddPage();

// set some text to print
$main_html = <<<EOD
Custom page header and footer are defined by extending the TCPDF class and overriding the Header() and Footer() methods.

<table>
<tbody>
 <tr class="odd"><td width="180"><span>Wilson</span> - Uploaded a Picture</td><td>6 hours ago</td> </tr>
 <tr class="even"><td width="180"><span>Wilson</span> - Responded to Poll</td><td>6 hours ago</td> </tr>
 <tr class="odd"><td width="180"><span>Robin Hood</span> - Updated Trip Profile</td><td>9 hours ago</td> </tr>
 <tr class="even"><td width="180"><span>Robin Hood</span> - Updated Trip Profile</td><td>9 hours ago</td> </tr>
 <tr class="odd"><td width="180"><span>Robin Hood</span> - Updated Trip Profile</td><td>9 hours ago</td> </tr>
 <tr class="even"><td width="180"><span>Robin Hood</span> - Updated Trip Profile</td><td>9 hours ago</td> </tr>
 <tr class="odd"><td width="180"><span>Shyamraj</span> - Edited the Golf Pairings</td><td>on 7/16/2010</td> </tr>
 <tr class="even"><td width="180"><span>Shyamraj</span> - Edited the Golf Pairings</td><td>on 7/16/2010</td> </tr>
 <tr class="odd"><td width="180"><span>Shyamraj</span> - Edited the Golf Pairings</td><td>on 7/16/2010</td> </tr>
 <tr class="even"><td width="180"><span>Shyamraj</span> - Edited the Golf Pairings</td><td>on 7/16/2010</td> </tr>
</tbody>
</table>

<table>
<tbody>
 <tr class="odd"><td width="180"><span>Wilson</span> - Uploaded a Picture</td><td>6 hours ago</td> </tr>
 <tr class="even"><td width="180"><span>Wilson</span> - Responded to Poll</td><td>6 hours ago</td> </tr>
 <tr class="odd"><td width="180"><span>Robin Hood</span> - Updated Trip Profile</td><td>9 hours ago</td> </tr>
 <tr class="even"><td width="180"><span>Robin Hood</span> - Updated Trip Profile</td><td>9 hours ago</td> </tr>
 <tr class="odd"><td width="180"><span>Robin Hood</span> - Updated Trip Profile</td><td>9 hours ago</td> </tr>
 <tr class="even"><td width="180"><span>Robin Hood</span> - Updated Trip Profile</td><td>9 hours ago</td> </tr>
 <tr class="odd"><td width="180"><span>Shyamraj</span> - Edited the Golf Pairings</td><td>on 7/16/2010</td> </tr>
 <tr class="even"><td width="180"><span>Shyamraj</span> - Edited the Golf Pairings</td><td>on 7/16/2010</td> </tr>
 <tr class="odd"><td width="180"><span>Shyamraj</span> - Edited the Golf Pairings</td><td>on 7/16/2010</td> </tr>
 <tr class="even"><td width="180"><span>Shyamraj</span> - Edited the Golf Pairings</td><td>on 7/16/2010</td> </tr>
</tbody>
</table>
<table>
<tbody>
 <tr class="odd"><td width="180"><span>Wilson</span> - Uploaded a Picture</td><td>6 hours ago</td> </tr>
 <tr class="even"><td width="180"><span>Wilson</span> - Responded to Poll</td><td>6 hours ago</td> </tr>
 <tr class="odd"><td width="180"><span>Robin Hood</span> - Updated Trip Profile</td><td>9 hours ago</td> </tr>
 <tr class="even"><td width="180"><span>Robin Hood</span> - Updated Trip Profile</td><td>9 hours ago</td> </tr>
 <tr class="odd"><td width="180"><span>Robin Hood</span> - Updated Trip Profile</td><td>9 hours ago</td> </tr>
 <tr class="even"><td width="180"><span>Robin Hood</span> - Updated Trip Profile</td><td>9 hours ago</td> </tr>
 <tr class="odd"><td width="180"><span>Shyamraj</span> - Edited the Golf Pairings</td><td>on 7/16/2010</td> </tr>
 <tr class="even"><td width="180"><span>Shyamraj</span> - Edited the Golf Pairings</td><td>on 7/16/2010</td> </tr>
 <tr class="odd"><td width="180"><span>Shyamraj</span> - Edited the Golf Pairings</td><td>on 7/16/2010</td> </tr>
 <tr class="even"><td width="180"><span>Shyamraj</span> - Edited the Golf Pairings</td><td>on 7/16/2010</td> </tr>
</tbody>
</table>

<table>
<tbody>
 <tr class="odd"><td width="180"><span>Wilson</span> - Uploaded a Picture</td><td>6 hours ago</td> </tr>
 <tr class="even"><td width="180"><span>Wilson</span> - Responded to Poll</td><td>6 hours ago</td> </tr>
 <tr class="odd"><td width="180"><span>Robin Hood</span> - Updated Trip Profile</td><td>9 hours ago</td> </tr>
 <tr class="even"><td width="180"><span>Robin Hood</span> - Updated Trip Profile</td><td>9 hours ago</td> </tr>
 <tr class="odd"><td width="180"><span>Robin Hood</span> - Updated Trip Profile</td><td>9 hours ago</td> </tr>
 <tr class="even"><td width="180"><span>Robin Hood</span> - Updated Trip Profile</td><td>9 hours ago</td> </tr>
 <tr class="odd"><td width="180"><span>Shyamraj</span> - Edited the Golf Pairings</td><td>on 7/16/2010</td> </tr>
 <tr class="even"><td width="180"><span>Shyamraj</span> - Edited the Golf Pairings</td><td>on 7/16/2010</td> </tr>
 <tr class="odd"><td width="180"><span>Shyamraj</span> - Edited the Golf Pairings</td><td>on 7/16/2010</td> </tr>
 <tr class="even"><td width="180"><span>Shyamraj</span> - Edited the Golf Pairings</td><td>on 7/16/2010</td> </tr>
</tbody>
</table>
<table>
<tbody>
 <tr class="odd"><td width="180"><span>Wilson</span> - Uploaded a Picture</td><td>6 hours ago</td> </tr>
 <tr class="even"><td width="180"><span>Wilson</span> - Responded to Poll</td><td>6 hours ago</td> </tr>
 <tr class="odd"><td width="180"><span>Robin Hood</span> - Updated Trip Profile</td><td>9 hours ago</td> </tr>
 <tr class="even"><td width="180"><span>Robin Hood</span> - Updated Trip Profile</td><td>9 hours ago</td> </tr>
 <tr class="odd"><td width="180"><span>Robin Hood</span> - Updated Trip Profile</td><td>9 hours ago</td> </tr>
 <tr class="even"><td width="180"><span>Robin Hood</span> - Updated Trip Profile</td><td>9 hours ago</td> </tr>
 <tr class="odd"><td width="180"><span>Shyamraj</span> - Edited the Golf Pairings</td><td>on 7/16/2010</td> </tr>
 <tr class="even"><td width="180"><span>Shyamraj</span> - Edited the Golf Pairings</td><td>on 7/16/2010</td> </tr>
 <tr class="odd"><td width="180"><span>Shyamraj</span> - Edited the Golf Pairings</td><td>on 7/16/2010</td> </tr>
 <tr class="even"><td width="180"><span>Shyamraj</span> - Edited the Golf Pairings</td><td>on 7/16/2010</td> </tr>
</tbody>
</table>

<table>
<tbody>
 <tr class="odd"><td width="180"><span>Wilson</span> - Uploaded a Picture</td><td>6 hours ago</td> </tr>
 <tr class="even"><td width="180"><span>Wilson</span> - Responded to Poll</td><td>6 hours ago</td> </tr>
 <tr class="odd"><td width="180"><span>Robin Hood</span> - Updated Trip Profile</td><td>9 hours ago</td> </tr>
 <tr class="even"><td width="180"><span>Robin Hood</span> - Updated Trip Profile</td><td>9 hours ago</td> </tr>
 <tr class="odd"><td width="180"><span>Robin Hood</span> - Updated Trip Profile</td><td>9 hours ago</td> </tr>
 <tr class="even"><td width="180"><span>Robin Hood</span> - Updated Trip Profile</td><td>9 hours ago</td> </tr>
 <tr class="odd"><td width="180"><span>Shyamraj</span> - Edited the Golf Pairings</td><td>on 7/16/2010</td> </tr>
 <tr class="even"><td width="180"><span>Shyamraj</span> - Edited the Golf Pairings</td><td>on 7/16/2010</td> </tr>
 <tr class="odd"><td width="180"><span>Shyamraj</span> - Edited the Golf Pairings</td><td>on 7/16/2010</td> </tr>
 <tr class="even"><td width="180"><span>Shyamraj</span> - Edited the Golf Pairings</td><td>on 7/16/2010</td> </tr>
</tbody>
</table>
EOD;

// print a block of text using Write()
//$pdf->Write($h=0, $txt, $link='', $fill=0, $align='C', $ln=true, $stretch=0, $firstline=false, $firstblock=false, $maxh=0);

$pdf->writeHTML($main_html, true, false, true, false, '');

// ---------------------------------------------------------

//Close and output PDF document
$pdf->Output('sample.pdf', 'I');

//============================================================+
// END OF FILE                                                
//============================================================+
?>
