$email = "yijiac40@gmail.com" 
 
$pass = "7ujm*IK<" 
 
$smtpServer = "smtp.gmail.com" 

$param1=$args[0] # text 
 
$msg = new-object Net.Mail.MailMessage 
$smtp = new-object Net.Mail.SmtpClient($smtpServer) 
$smtp.EnableSsl = $true 
$msg.From = "$email"  
$msg.To.Add("yeejiac@gmail.com") 
$msg.BodyEncoding = [system.Text.Encoding]::Unicode 
$msg.SubjectEncoding = [system.Text.Encoding]::Unicode 
$msg.IsBodyHTML = $true  
$msg.Subject = "Error Log" 
$msg.Body = "<h2> $1 </h2> </br> $param1"

$SMTP.Credentials = New-Object System.Net.NetworkCredential("$email", "$pass"); 
$smtp.Send($msg)