<!DOCTYPE html>
<html lang="en">

<head>
    <meta charset="utf-8">
    <meta name="viewport" content="width=device-width, initial-scale=1.0, shrink-to-fit=no">
    <title>select</title>
    <link rel="stylesheet" href="https://cdn.jsdelivr.net/npm/bootstrap@5.0.2/dist/css/bootstrap.min.css">
    <link rel="stylesheet" href="https://cdnjs.cloudflare.com/ajax/libs/font-awesome/4.7.0/css/font-awesome.min.css">
    <link rel="stylesheet" href="https://cdnjs.cloudflare.com/ajax/libs/animate.css/3.5.2/animate.min.css">
</head>

<body class="d-md-flex align-items-md-center justify-content-xxl-center align-items-xxl-start" style="background: url(&quot;img/header.jpg&quot;);">
    <div class="container" style="margin-top: 18vh;padding: 20px;background: #f7f3f3;border-radius: 15px;">
        <div class="row" style="height: 330px;">
            <div class="col-md-6 d-xxl-flex justify-content-xxl-center align-items-xxl-start">
                <div class="d-xxl-flex justify-content-xxl-center align-items-xxl-center" style="padding: 5px;height: 330px;">
                    <div class="text-start" style="margin-top: 0px;">
                        <div>
                            <p class="text-center" data-bss-hover-animate="pulse" style="font-size: 25px;font-weight: bold;border-radius: 20px;color: #4688d6;border: 3px outset #4688d6 ;"><i class="fa fa-chevron-circle-down" style="margin-right: 5px;"></i>Which device?</p>
                        </div>
                        <div style="background: #e3e3e3;border-radius: 25px;padding: 10px;">
                            <p style="margin-bottom: 0px;">Choose the required device's id</p>
                        </div>
                        <div style="background: #e3e3e3;border-radius: 25px;padding: 10px;margin-top: 15px;"><select style="background: #e3e3e3;border: 3px none var(--bs-blue) ;">
                                <option value="1" selected="">Device ID</option>
                                <option value="2">This is item 2</option>
                                <option value="3">This is item 3</option>
                            </select></div>
                        <div style="background: #4688d6;border-radius: 25px;padding: 10px;margin-top: 15px;">
                            <p class="text-center" style="margin-bottom: 0px;color: rgb(255,255,255);">Submit</p>
                        </div>
                        <div>
                            <p class="text-center" style="margin-top: 10px;">You will be redirected to the main page after submitting</p>
                        </div>
                    </div>
                </div>
            </div>
            <div class="col-md-6 d-xxl-flex bounce animated" style="background: url(&quot;img/select.jpg&quot;) center / contain no-repeat;border-radius: 15px;border-width: 3px;border-style: none;">
                <div></div>
            </div>
        </div>
    </div>
    <script src="https://cdn.jsdelivr.net/npm/bootstrap@5.0.2/dist/js/bootstrap.bundle.min.js"></script>
    <script src="../js/bs-init.js></script>
</body>

</html>