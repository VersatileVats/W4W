<!DOCTYPE html>
<html lang="en">

<head>
    <meta charset="utf-8">
    <meta name="viewport" content="width=device-width, initial-scale=1.0, shrink-to-fit=no">
    <title>Sign In Page</title>
    <link rel="stylesheet" href="https://cdn.jsdelivr.net/npm/bootstrap@5.0.2/dist/css/bootstrap.min.css">
    <link rel="stylesheet" href="https://cdnjs.cloudflare.com/ajax/libs/font-awesome/4.7.0/css/font-awesome.min.css">
    <link rel="stylesheet" href="https://cdnjs.cloudflare.com/ajax/libs/animate.css/3.5.2/animate.min.css">
</head>

<body class="d-md-flex align-items-md-center justify-content-xxl-center align-items-xxl-start" style="background: url(&quot;img/header.jpg&quot;);">
    <div class="container" style="padding: 20px;background: #ffffff;border-radius: 15px;height: 75vh;margin-top: 15vh;">
        <div class="row" style="height: 330px;">
            <div class="col-md-6 d-xxl-flex justify-content-xxl-center align-items-xxl-start">
                <div class="d-md-flex d-xxl-flex justify-content-md-center align-items-md-center justify-content-xxl-center align-items-xxl-center" style="padding: 5px;height: 70vh;">
                    <div class="text-start" style="margin-top: 18px;">
                        <div>
                            <p class="text-center pulse animated" style="font-size: 25px;font-weight: bold;letter-spacing: 0px;border-radius: 20px;color: #4688d6;border: 3px inset #4688d6;padding: 0px 85px;"><i class="fa fa-th-list" style="margin-right: 5px;"></i>User Sign In</p>
                        </div>
                        <div data-bss-hover-animate="pulse" style="background: #e3e3e3;border-radius: 25px;padding: 10px;"><input type="email" style="background: rgba(255,255,255,0);border-style: none;margin-left: 11px;color: #4688d6;" placeholder="Email" required=""></div>
                        <div data-bss-hover-animate="pulse" style="background: #e3e3e3;border-radius: 25px;padding: 10px;margin-top: 15px;"><input type="text" style="background: rgba(255,255,255,0);border-style: none;margin-left: 11px;color: #4688d6;" placeholder="Username" required=""></div>
                        <div data-bss-hover-animate="pulse" style="background: #e3e3e3;border-radius: 25px;padding: 10px;margin-top: 15px;"><input type="password" style="background: rgba(255,255,255,0);border-style: none;margin-left: 11px;color: #4688d6;" placeholder="Password" required="" title="Minimum 8 characters and 1 special character required" pattern="&quot;^(?=.*[a-z])(?=.*[A-Z])(?=.*\d)[a-zA-Z\d]{9,}$&quot;"></div>
                        <div data-bss-hover-animate="pulse" style="background: #e3e3e3;border-radius: 25px;padding: 10px;margin-top: 15px;"><input type="password" style="background: rgba(255,255,255,0);border-style: none;margin-left: 11px;color: #4688d6;" placeholder="Confirm Password" required="" title="Minimum 8 characters and 1 special character required"></div>
                        <div data-bss-hover-animate="pulse" style="background: #e3e3e3;border-radius: 25px;padding: 10px;margin-top: 15px;"><input type="text" style="background: rgba(255,255,255,0);border-style: none;margin-left: 11px;color: #4688d6;" placeholder="Device ID" required=""></div>
                        <div data-bss-hover-animate="pulse" style="background: #e3e3e3;border-radius: 25px;padding: 10px;margin-top: 15px;"><input type="text" style="background: rgba(255,255,255,0);border-style: none;margin-left: 11px;color: #4688d6;" placeholder="API Key" required="" minlength="25"></div>
                        
                        <div class="d-grid gap-2">
                            <button class="btn btn-primary" style="background: #4688d6;border-radius: 25px;padding: 10px;margin-top: 15px;"type="submit">
                                Login
                            </button>
                        </div>
                    </div>
                </div>
            </div>
            <div class="col-md-6 d-xxl-flex" data-bss-hover-animate="pulse" style="background: url(&quot;img/signin.jpg&quot;) center / contain no-repeat;border-radius: 15px;border-width: 3px;border-style: none;">
                <div></div>
            </div>
        </div>
    </div>
    <script src="https://cdn.jsdelivr.net/npm/bootstrap@5.0.2/dist/js/bootstrap.bundle.min.js"></script>
    <script src="../js/bs-init.js"></script>
</body>

</html>