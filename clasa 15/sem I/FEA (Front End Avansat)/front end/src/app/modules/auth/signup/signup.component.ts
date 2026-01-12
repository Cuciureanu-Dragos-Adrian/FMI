import { Component, OnInit } from '@angular/core';
import { AbstractControl, FormControl, FormGroup } from '@angular/forms';
import { AbstractConstructor } from '@angular/material/core/common-behaviors/constructor';
import { Router } from '@angular/router';
import { AuthService } from 'src/app/services/auth.service';

@Component({
  selector: 'app-signup',
  templateUrl: './signup.component.html',
  styleUrls: ['./signup.component.scss']
})
export class SignupComponent implements OnInit {

  public signupForm: FormGroup = new FormGroup(
    {
      email: new FormControl(''),
      username: new FormControl(''),
      password: new FormControl(''),
      verifyPassword: new FormControl(''),
    }
  );

  constructor(
    private router: Router,
    private authService: AuthService,
  ) { }

  //getters
  get email(): AbstractControl
  {
    return this.signupForm.get('email')!;
  }

  get username(): AbstractControl
  {
    return this.signupForm.get('username')!;
  }

  get password(): AbstractControl
  {
    return this.signupForm.get('password')!;
  }

  get verifyPassword(): AbstractControl
  {
    return this.signupForm.get('verifyPassword')!;
  }

  ngOnInit(): void {
  }

  public login(): void 
  {
    this.router.navigate(['/auth/login']);
  }
  
  public signup(): void 
  {
    console.log(this.signupForm.value);
    this.authService.signup(this.signupForm.value).subscribe({
      next:(result) => {
        this.router.navigate(['/auth/login']);
      },
      error:(error) =>{
        console.log(error);
      }
    });
    //this.router.navigate(['/auth/login']);
  }
}
