dec = $(patsubst .%,%,$1)

not = $(if $1,,.)

lteq = $(if $1,$(if $(findstring $1,$2),.,),.)
gteq = $(if $2,$(if $(findstring $2,$1),.,),.)
eq = $(and $(call lteq,$1,$2),$(call gteq,$1,$2))
lt = $(and $(call lteq,$1,$2),$(call not,$(call gteq,$1,$2)))

add = $1$2
sub = $(if $(call not,$2),$1,$(call sub,$(call dec,$1),$(call dec,$2)))
mul = $(if $(call not,$2),$2,$(call add,$1,$(call mul,$1,$(call dec,$2))))
fibo = $(if $(call lt,$1,..),$1,$(call add,$(call fibo,$(call dec,$1)),$(call fibo,$(call sub,$1,..))))
fact = $(if $(call lt,$1,..),.,$(call mul,$1,$(call fact,$(call dec,$1))))

numeral = $(words $(subst .,. ,$1))

go = $(or $(info $(call numeral,$(call mul,$1,$1)) $(call numeral,$(call fibo,$1)) $(call numeral,$(call fact,$1)) ),$(call go,.$1))

_ := $(call go,)
