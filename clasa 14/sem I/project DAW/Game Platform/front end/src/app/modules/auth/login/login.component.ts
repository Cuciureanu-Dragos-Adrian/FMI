import { Component, OnInit } from '@angular/core';
import { AbstractControl, FormControl, FormGroup } from '@angular/forms';
import { Router } from '@angular/router';
import { AuthService } from 'src/app/services/auth.service';
import { DataService } from 'src/app/services/data.service';

@Component({
  selector: 'app-login',
  templateUrl: './login.component.html',
  styleUrls: ['./login.component.scss']
})
export class LoginComponent implements OnInit {

  public loginForm: FormGroup = new FormGroup(
    {
      username: new FormControl(''),
      password: new FormControl(''),
    }
  );
  private token: string = '';

  constructor(
    private router: Router,
    private dataService: DataService,
    private authService: AuthService
  ) { }

  //getters
  get username(): AbstractControl
  {
    return this.loginForm.get('username')!;
  }

  get password(): AbstractControl
  {
    return this.loginForm.get('password')!;
  }

  ngOnInit(): void {
  }

  public login(): void 
  {
    this.dataService.changeUserData(this.loginForm.value);

    this.authService.login(this.loginForm.value).subscribe({
      next:(result) => {
        console.log(result);
        this.token = result;
        localStorage.setItem('Role', result.token);
        this.router.navigate(['/dashboard']);
      },
      error:(error) =>{
        console.log(error);
      }
    })
  }
  
  public signup(): void 
  {
    this.router.navigate(['/auth/signup']);
  }
}
