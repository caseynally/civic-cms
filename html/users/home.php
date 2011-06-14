<?php
/**
 * @copyright Copyright (C) 2006,2007,2008 City of Bloomington, Indiana. All rights reserved.
 * @license http://www.gnu.org/licenses/agpl.txt GNU/AGPL, see LICENSE.txt
 * @author Cliff Ingham <inghamn@bloomington.in.gov>
 * @param GET authenticationMethod
 */
verifyUser('Administrator');

$authenticationMethod = isset($_GET['authenticationMethod']) ? $_GET['authenticationMethod'] : 'LDAP';

$users = new UserList();
$users->find(array('authenticationMethod'=>$authenticationMethod));
$userList = new Block('users/userList.inc');
$userList->userList = $users;
$userList->authenticationMethod = $authenticationMethod;


$template = isset($_GET['format']) ? new Template('default',$_GET['format']) : new Template();
$template->blocks[] = $userList;
echo $template->render();
