<?php
// Call UserListTest::main() if this source file is executed directly.
if (!defined('PHPUnit_MAIN_METHOD')) {
    define('PHPUnit_MAIN_METHOD', 'UserListTest::main');
}

require_once 'PHPUnit/Framework.php';

if (!defined('APPLICATION_HOME')) { include dirname(__FILE__).'/../configuration.inc'; }
require_once APPLICATION_HOME.'/classes/UserList.inc';

/**
 * Test class for UserList.
 * Generated by PHPUnit on 2007-10-04 at 11:49:15.
 */
class UserListTest extends PHPUnit_Framework_TestCase {
    /**
     * Runs the test methods of this class.
     *
     * @access public
     * @static
     */
    public static function main() {
        require_once 'PHPUnit/TextUI/TestRunner.php';

        $suite  = new PHPUnit_Framework_TestSuite('UserListTest');
        $result = PHPUnit_TextUI_TestRunner::run($suite);
    }

    /**
     * Sets up the fixture, for example, opens a network connection.
     * This method is called before a test is executed.
     *
     * @access protected
     */
    protected function setUp() {
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
     * @todo Implement testFind().
     */
    public function testFind() {
        // Remove the following lines when you implement this test.
        $this->markTestIncomplete(
          'This test has not been implemented yet.'
        );
    }

    /**
     * @todo Implement testSearch().
     */
    public function testSearch() {
        // Remove the following lines when you implement this test.
        $this->markTestIncomplete(
          'This test has not been implemented yet.'
        );
    }
}

// Call UserListTest::main() if this source file is executed directly.
if (PHPUnit_MAIN_METHOD == 'UserListTest::main') {
    UserListTest::main();
}
?>