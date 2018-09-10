<?php
require('users_db.php'); // $users

if($_GET['show_source'] === '1') {
    highlight_file(__FILE__);
    exit;
}

if($_GET['logout'] === '1') {
    setcookie('user', '', 0);
    header('Location: ./');
}

function set_user($user_data)
{
    global $user, $secret;

    $user = [
        'name' => $user_data['name'],
        'admin' => $user_data['admin']
    ];

    $serialized = http_build_query($user);
    $sig = md5(md5($secret).$serialized);
    $all = base64_encode("{$sig}#{$serialized}");
    setcookie('user', $all, time()+3600);
}

$error = null;

function load_user()
{
    global $secret, $error;

    if(empty($_COOKIE['user'])) {
        return null;
    }

    list($sig, $serialized) = explode('#', base64_decode($_COOKIE['user']), 2);

    if(md5(md5($secret).$serialized) !== $sig) {
        $error = 'Invalid session';
        return false;
    }

    parse_str($serialized, $user);
    return $user;
}

$user = load_user();

if(!empty($_POST['name']) && !empty($_POST['password'])) {
    $user = false;
    foreach($users as $u) {
        if($u['name'] === $_POST['name'] && $u['password'] === $_POST['password']) {
            set_user($u);
        }
    }
}
?><!DOCTYPE html>
<html lang="en">
<head>
    <meta charset="UTF-8">
    <title>Login As Admin 2</title>
    <meta name="viewport" content="width=device-width, initial-scale=1">
    <link rel="stylesheet" href="/bootstrap/css/bootstrap.min.css" media="all">
</head>
<body>
    <div class="jumbotron">
        <div class="container">
            <h1>Login as Admin 2</h1>
        </div>
    </div>

    <div class="container">
        <div class="navbar">
            <div class="container-fluid">
                <div class="navbar-header">
                    <a class="navbar-brand" href="/">Please Hack Me</a>
                </div>
                <ul class="nav navbar-nav">
                    <li>
                        <a href="/scoreboard">Scoreboard</a>
                    </li>
                    <li>
                        <a href="?show_source=1" target="_blank">Source Code</a>
                    </li>
<?php if($user): ?>
                    <li>
                        <a href="?logout=1">Logout</a>
                    </li>
<?php endif; ?>
                </ul>
            </div>
        </div>
    </div>

<?php if($error !== null): ?>
    <div class="container">
        <div class="alert alert-danger"><?=$error?></div>
    </div>
<?php endif; ?>

    <div class="container">
        <div class="col-md-6 col-md-offset-3">
<?php if(!$user): ?>
<?php if($user === false): ?>
            <div class="alert alert-danger">Login failed</div>
<?php endif; ?>
            <form action="." method="POST">
                <div class="form-group">
                    <label for="name">User:</label>
                    <input id="name" class="form-control" type="text" name="name" placeholder="User">
                </div>
                <div class="form-group">
                    <label for="password">Pass:</label>
                    <input id="password" class="form-control" type="text" name="password" placeholder="Password">
                </div>
                <div class="form-group">
                    <input class="form-control btn btn-primary" type="submit" value="Login">
                </div>
            </form>

            <div>
                <p>
                    You can login with <code>guest</code> / <code>guest</code>.
                </p>
            </div>
<?php else: ?>
            <h3>Hi, <?=htmlentities($user['name'])?></h3>

            <h4><?=sprintf("You %s admin!", $user['admin'] ? "are" : "are not")?></h4>

            <?php if($user['admin']) printf("<code>%s</code>", htmlentities($flag)); ?>
<?php endif; ?>
        </div>
    </div>
</body>
</html>