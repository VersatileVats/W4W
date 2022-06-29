<!DOCTYPE html>
<html lang="en">

<head>
    <meta charset="utf-8">
    <meta name="viewport" content="width=device-width, initial-scale=1.0, shrink-to-fit=no">
    <title>login</title>
    <link rel="stylesheet" href="https://cdn.jsdelivr.net/npm/bootstrap@5.0.2/dist/css/bootstrap.min.css">
    <link rel="stylesheet" href="https://cdnjs.cloudflare.com/ajax/libs/font-awesome/4.7.0/css/font-awesome.min.css">
    <link rel="stylesheet" href="https://cdnjs.cloudflare.com/ajax/libs/animate.css/3.5.2/animate.min.css">
</head>

<body class="d-md-flex align-items-md-center justify-content-xxl-center align-items-xxl-start" style="background: url(&quot;img/header.jpg&quot;);">
    <div class="container" style="margin-top: 18vh;padding: 20px;background: #f7f3f3;border-radius: 15px;">
        <div class="row" style="height: 330px;">
            <div class="col-md-6 d-xxl-flex" data-bss-hover-animate="pulse" style="background: url(&quot;img/login.jpg&quot;) center / contain no-repeat;border-radius: 15px;border-width: 3px;border-style: none;">
                <div></div>
            </div>
            <div class="col-md-6 d-xxl-flex justify-content-xxl-center align-items-xxl-start">
                <div class="d-md-flex d-xxl-flex justify-content-md-center align-items-md-center justify-content-xxl-center align-items-xxl-center" style="padding: 5px;height: 330px;">
                    <div class="text-start" style="margin-top: 18px;">
                        <div>
                            <p class="text-center pulse animated" style="font-size: 25px;font-weight: bold;border-radius: 20px;color: #4688d6;border: 3px inset #4688d6 ;"><i class="fa fa-user" style="margin-right: 5px;"></i>User Signup</p>
                        </div>

                        <!-- Form & i/p fields -->
                        <form action="script.php" method="post">
                            <div style="background: #e3e3e3;border-radius: 25px;padding: 10px;"><i class="fa fa-envelope" style="margin-left: 15px;color: rgb(152,152,152);"></i>
                                <input type="text" style="background: rgba(255,255,255,0);border-style: none;margin-left: 11px;color: rgb(152,152,152);" placeholder="Email" required>
                            </div>
                        </form>

                        <div>
                            <p class="text-center" style="margin-top: 10px;">
                                New to the website? Click <a href="login.php">here</a> to create account
                            </p>
                        </div>
                    </div>
                </div>
            </div>
        </div>
    </div>
    <script src="../js/bs-init.js"></script>
</body>

</html>
