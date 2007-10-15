<?php
// Call SectionTest::main() if this source file is executed directly.
if (!defined('PHPUnit_MAIN_METHOD')) {
    define('PHPUnit_MAIN_METHOD', 'SectionTest::main');
}

require_once 'PHPUnit/Framework.php';

require_once APPLICATION_HOME.'/classes/Section.inc';

/**
 * Test class for Section.
 * Generated by PHPUnit on 2007-10-04 at 11:49:13.
 */
class SectionTest extends PHPUnit_Framework_TestCase {
    /**
     * Runs the test methods of this class.
     *
     * @access public
     * @static
     */
    public static function main() {
        require_once 'PHPUnit/TextUI/TestRunner.php';

        $suite  = new PHPUnit_Framework_TestSuite('SectionTest');
        $result = PHPUnit_TextUI_TestRunner::run($suite);
    }

    /**
     * Sets up the fixture, for example, opens a network connection.
     * This method is called before a test is executed.
     *
     * @access protected
     */
    protected function setUp() {
    	$_SESSION['USER'] = new User(1);


    }

    /**
     * Tears down the fixture, for example, closes a network connection.
     * This method is called after a test is executed.
     *
     * @access protected
     */
    protected function tearDown() {
    }

    /**
     * Test that section changes get written back to the database
     */
    public function testSave() {
    	# Test update
    	$section = new Section(1);
    	$section->setNickname('changed');
    	try { $section->save(); }
    	catch(Exception $e) { $this->fail('Section saving threw exception'.$e->getMessage()); }

		$changed = new Section(1);
		$this->assertTrue($changed->getNickname()=='changed','Section was not saved to the database');


		# Test insert
		$section = new Section();
		$section->setName('Test Section');
		$section->setDepartments(array(1));
		try { $section->save(); }
		catch(Exception $e) { $this->fail('Section insert threw exception '.$e->getMessage()); }
		$this->assertTrue($section->getId()!='','New section did not get an ID from the database'.$section->getId());
		$this->assertNotNull($section->getId(),'New Section did not get an ID from the database');

		$this->assertNotNull($section->getSectionDocument_id(),'New section did not create a home document'.$section->getSectionDocument_id());

		$section->delete();
    }

    /**
     * @todo Implement testDelete().
     */
    public function testDelete() {
        // Remove the following lines when you implement this test.
        $this->markTestIncomplete(
          'This test has not been implemented yet.'
        );
        /*
    	# Try and delete the New Section we just created
    	$PDO = Database::getConnection();
    	$query = $PDO->prepare('select id from sections where name=?');
    	$query->execute(array('New Section'));
    	$result = $query->fetchAll();
    	$id = $result[0]['id'];

    	$section = new Section($id);
    	$section->delete();

    	$query = $PDO->prepare('select id from sections where name=?');
    	$query->execute(array('New Section'));
    	$result = $query->fetchAll();
    	$this->assertTrue(count($result)==0,'Section was not deleted');
    	*/
    }

    /**
     * @todo Implement testGetChildNodes().
     */
    public function testGetChildNodes() {
        // Remove the following lines when you implement this test.
        $this->markTestIncomplete(
          'This test has not been implemented yet.'
        );
    }

    /**
     * @todo Implement testGetParentNodes().
     */
    public function testGetParentNodes() {
        // Remove the following lines when you implement this test.
        $this->markTestIncomplete(
          'This test has not been implemented yet.'
        );
    }

    /**
     * @todo Implement testHasChildren().
     */
    public function testHasChildren() {
        // Remove the following lines when you implement this test.
        $this->markTestIncomplete(
          'This test has not been implemented yet.'
        );
    }

    /**
     * @todo Implement testGetChildren().
     */
    public function testGetChildren() {
        // Remove the following lines when you implement this test.
        $this->markTestIncomplete(
          'This test has not been implemented yet.'
        );
    }

    /**
     * @todo Implement testGetParents().
     */
    public function testGetParents() {
        // Remove the following lines when you implement this test.
        $this->markTestIncomplete(
          'This test has not been implemented yet.'
        );
    }

    /**
     * @todo Implement testHasParent().
     */
    public function testHasParent() {
        // Remove the following lines when you implement this test.
        $this->markTestIncomplete(
          'This test has not been implemented yet.'
        );
    }

    /**
     * @todo Implement testGetAncestors().
     */
    public function testGetAncestors() {
        // Remove the following lines when you implement this test.
        $this->markTestIncomplete(
          'This test has not been implemented yet.'
        );
    }

    /**
     * @todo Implement testGetDescendants().
     */
    public function testGetDescendants() {
        // Remove the following lines when you implement this test.
        $this->markTestIncomplete(
          'This test has not been implemented yet.'
        );
    }

    /**
     * @todo Implement testGetDepartments().
     */
    public function testGetDepartments() {
        // Remove the following lines when you implement this test.
        $this->markTestIncomplete(
          'This test has not been implemented yet.'
        );
    }

    /**
     * @todo Implement testSetDepartments().
     */
    public function testSetDepartments() {
        // Remove the following lines when you implement this test.
        $this->markTestIncomplete(
          'This test has not been implemented yet.'
        );
    }

    /**
     * @todo Implement testHasDepartment().
     */
    public function testHasDepartment() {
        // Remove the following lines when you implement this test.
        $this->markTestIncomplete(
          'This test has not been implemented yet.'
        );
    }

    /**
     * Test that we can determine whehter a section has a particular document,
     * using either a Document object or a document_id
     */
    public function testHasDocument()
    {
		$section = new Section(1);
		$document = $section->getDocument();

		$this->assertTrue($section->hasDocument($document)==1,'Could not determine based on Document object');
		$this->assertTrue($section->hasDocument($document->getId())==1,'Could not determine based on document_id');
    }

    /**
     * @todo Implement testGetDocuments().
     */
    public function testGetDocuments() {
        // Remove the following lines when you implement this test.
        $this->markTestIncomplete(
          'This test has not been implemented yet.'
        );
    }

    /**
     * @todo Implement testGetDocumentLinks().
     */
    public function testGetDocumentLinks() {
        // Remove the following lines when you implement this test.
        $this->markTestIncomplete(
          'This test has not been implemented yet.'
        );
    }

    /**
     * @todo Implement testGetWidgets().
     */
    public function testGetWidgets() {
        // Remove the following lines when you implement this test.
        $this->markTestIncomplete(
          'This test has not been implemented yet.'
        );
    }

    /**
     * @todo Implement testHasWidget().
     */
    public function testHasWidget() {
        // Remove the following lines when you implement this test.
        $this->markTestIncomplete(
          'This test has not been implemented yet.'
        );
    }

    /**
     * @todo Implement testPermitsPostingBy().
     */
    public function testPermitsPostingBy() {
		# Find a limited user
		#$list = new UserList(array('role'=>'Content Creator'));
		#$user = $list[0];
		$user = new User(8);

		# Find a section for their department
		#$list = new SectionList(array('department_id'=>$user->getDepartment_id()));
		#$section = $list[0];
		$section = new Section(121);

		# The user should be able to post to that department
		$this->assertTrue($section->permitsPostingBy($user),'User could not post to their section');
    }

    /**
     * @todo Implement testPermitsEditingBy().
     */
    public function testPermitsEditingBy() {
        // Remove the following lines when you implement this test.
        $this->markTestIncomplete(
          'This test has not been implemented yet.'
        );
    }

    /**
     * @todo Implement testGetURL().
     */
    public function testGetURL() {
        // Remove the following lines when you implement this test.
        $this->markTestIncomplete(
          'This test has not been implemented yet.'
        );
    }

    /**
     * @todo Implement test__toString().
     */
    public function test__toString() {
        // Remove the following lines when you implement this test.
        $this->markTestIncomplete(
          'This test has not been implemented yet.'
        );
    }

    /**
     * @todo Implement testGetId().
     */
    public function testGetId() {
        // Remove the following lines when you implement this test.
        $this->markTestIncomplete(
          'This test has not been implemented yet.'
        );
    }

    /**
     * @todo Implement testGetName().
     */
    public function testGetName() {
        // Remove the following lines when you implement this test.
        $this->markTestIncomplete(
          'This test has not been implemented yet.'
        );
    }

    /**
     * @todo Implement testGetNickname().
     */
    public function testGetNickname() {
        // Remove the following lines when you implement this test.
        $this->markTestIncomplete(
          'This test has not been implemented yet.'
        );
    }

    /**
     * @todo Implement testGetDocument_id().
     */
    public function testGetDocument_id() {
        // Remove the following lines when you implement this test.
        $this->markTestIncomplete(
          'This test has not been implemented yet.'
        );
    }

    /**
     * Test whether we can get a document object for the home document
     */
    public function testGetDocument() {
    	$section = new Section(1);
    	$this->assertTrue($section->getDocument() instanceof Document,'Could not get the home document object');
    }

    /**
     * @todo Implement testSetName().
     */
    public function testSetName() {
        // Remove the following lines when you implement this test.
        $this->markTestIncomplete(
          'This test has not been implemented yet.'
        );
    }

    /**
     * @todo Implement testSetNickname().
     */
    public function testSetNickname() {
        // Remove the following lines when you implement this test.
        $this->markTestIncomplete(
          'This test has not been implemented yet.'
        );
    }

    /**
     * @todo Implement testSetDocument_id().
     */
    public function testSetDocument_id() {
        // Remove the following lines when you implement this test.
        $this->markTestIncomplete(
          'This test has not been implemented yet.'
        );
    }

    /**
     * @todo Implement testSetDocument().
     */
    public function testSetDocument() {
        // Remove the following lines when you implement this test.
        $this->markTestIncomplete(
          'This test has not been implemented yet.'
        );
    }
}

// Call SectionTest::main() if this source file is executed directly.
if (PHPUnit_MAIN_METHOD == 'SectionTest::main') {
    SectionTest::main();
}
?>
