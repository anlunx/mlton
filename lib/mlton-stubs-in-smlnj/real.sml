type int = Int32.int
   
signature REAL =
   sig
      type real

      structure Math: MATH where type real = real

      val != : real * real -> bool
      val * : real * real -> real
      val *+ : real * real * real -> real
      val *- : real * real * real -> real
      val + : real * real -> real
      val - : real * real -> real
      val / : real * real -> real
      val <  : real * real -> bool
      val <= : real * real -> bool
      val == : real * real -> bool
      val >  : real * real -> bool
      val >= : real * real -> bool
      val ?= : real * real -> bool
      val abs: real -> real
      val checkFloat: real -> real
      val class: real -> IEEEReal.float_class
      val compare: real * real -> order
      val compareReal: real * real -> IEEEReal.real_order
      val copySign: real * real -> real
      val fmt: StringCvt.realfmt -> real -> string
      val fromDecimal: IEEEReal.decimal_approx -> real option
      val fromInt: int -> real
      val fromLarge: IEEEReal.rounding_mode -> LargeReal.real -> real
      val fromLargeInt: LargeInt.int -> real
      val fromManExp: {man: real, exp: int} -> real
      val fromString: string -> real option
      val isFinite: real -> bool
      val isNan: real -> bool
      val isNormal: real -> bool
      val max: real * real -> real
      val maxFinite: real
      val min: real * real -> real
      val minNormalPos: real
      val minPos: real
      val negInf: real
      val nextAfter: real * real -> real
      val posInf: real
      val precision: int
      val radix: int
      val realCeil: real -> real
      val realFloor: real -> real
      val realMod: real -> real
      val realTrunc: real -> real
      val rem: real * real -> real
      val round: real -> Int.int
      val sameSign: real * real -> bool
      val scan: (char, 'a) StringCvt.reader -> (real, 'a) StringCvt.reader
      val sign: real -> int
      val signBit: real -> bool
      val split: real -> {whole: real, frac: real}
      val toDecimal: real -> IEEEReal.decimal_approx
      val toInt: IEEEReal.rounding_mode -> real -> int
      val toLarge: real -> LargeReal.real
      val toLargeInt: IEEEReal.rounding_mode -> real -> LargeInt.int
      val toManExp: real -> {man: real, exp: int}
      val toString: real -> string
      val unordered: real * real -> bool
      val ~ : real -> real
     val ceil: real -> Int.int
     val floor: real -> Int.int 
     val trunc: real -> Int.int 
   end

structure Real: REAL =
   struct
      open Real

      datatype z = datatype IEEEReal.float_class
      datatype z = datatype IEEEReal.rounding_mode

      fun fromLargeInt i =
	 valOf (Real.fromString (LargeInt.toString i))

      val toLargeInt: IEEEReal.rounding_mode -> real -> LargeInt.int =
	 fn mode => fn x =>
	 case class x of
	    INF => raise Overflow
	  | NAN _ => raise Domain
	  | ZERO => 0
	  | _ =>
	       let
		  val x =
		     case mode of
			TO_NEAREST =>
			   let
			      val x1 = realFloor x
			      val x2 = realCeil x
			   in
			      if abs (x - x1) < abs (x - x2)
				 then x1
			      else x2
			   end
		      | TO_NEGINF => realFloor x
		      | TO_POSINF => realCeil x
		      | TO_ZERO => realTrunc x
	       in
		  valOf (LargeInt.fromString (fmt (StringCvt.FIX (SOME 0)) x))
	       end

      open OpenInt32

      local
	 fun make m r = Pervasive.Int32.fromLarge (toLargeInt m r)
	 datatype z = datatype IEEEReal.rounding_mode
      in
	 val floor = make TO_NEGINF
	 val ceil = make TO_POSINF
	 val round = make TO_NEAREST
	 val trunc = make TO_ZERO
      end

      val radix = fromInt radix
      val precision = fromInt precision
      val sign = fromInt o sign
      fun toManExp x =
	 let
	    val {man, exp} = Real.toManExp x
	 in
	    {man = man, exp = fromInt exp}
	 end
      fun fromManExp {man, exp} =
	 Real.fromManExp {man = man, exp = toInt exp}
      fun toInt m x = Pervasive.Int32.fromLarge (toLargeInt m x)
      val fromInt = fromLargeInt o Pervasive.Int32.toLarge

      val fromDecimal = SOME o fromDecimal
   end
